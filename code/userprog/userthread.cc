#ifdef CHANGED

#include "system.h"
#include "userthread.h"


int do_UserThreadCreate(int f, int arg, int callback) {

    int new_tId = threadbitmap->Find();
    if (new_tId > 0) {
        Thread* newThread = new Thread ("slave", new_tId);

        struct struct_user_thread* args = new (struct struct_user_thread)();
        args->f = f;
        args->arg = arg;
        args->callback = callback;

        newThread->Fork(StartUserThread, (int)(args));
    }
    else
        return -1;

    return new_tId;
}

int do_UserThreadExit() {
    // Clear the bitmap
    threadbitmap->Clear(currentThread->getId());

    // Kill the thread
    currentThread->Finish();

    return 0;
}

void StartUserThread(int f) {

    struct_user_thread* args;
    args = (struct_user_thread*) f;

    currentThread->space->InitRegisters();
    currentThread->space->RestoreState();

    unsigned int regdpl = currentThread->getId()*PageThread*PageSize;
    machine->WriteRegister(StackReg, currentThread->space->getNumPages()*PageSize - regdpl - 16);

    machine->WriteRegister(PCReg, args->f); // PC
    machine->WriteRegister(NextPCReg, args->f + 4); // next PC
    machine->WriteRegister(4, args->arg); // R4 (arg)
    machine->WriteRegister(RetAddrReg, args->callback); // callback

    delete args;

    machine->Run();
}

#endif
