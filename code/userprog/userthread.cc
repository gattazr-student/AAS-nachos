#ifdef CHANGED

#include "system.h"
#include "userthread.h"


int do_UserThreadCreate(int f, int arg) {

    int new_tId = threadbitmap->Find();
    if (new_tId > 0) {
        Thread* newThread = new Thread ("slave", new_tId);

        struct struct_user_thread* args = new (struct struct_user_thread)();
        args->f = f;
        args->arg = arg;

        newThread->Fork(StartUserThread, (int)(args));
    }
    else
        return -1;

    return 0;
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

    machine->WriteRegister(PCReg, args->f);
    machine->WriteRegister(NextPCReg, args->f + 4);
    machine->WriteRegister(4, args->arg);

    delete args;

    machine->Run();
}

#endif
