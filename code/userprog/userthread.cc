#ifdef CHANGED

#include "system.h"
#include "userthread.h"

int do_UserThreadCreate(int f, int arg) {
    Thread* newThread = new Thread ("slave");
    //newThread->setStatus(JUST_CREATED);     déjà fait dans le constructeur

    //TODO memoire
    
    //To malloc
    struct struct_user_thread args;
    args.f = f;
    args.arg = arg;
    
    newThread->Fork(StartUserThread, (int)(&args));
    
    return 0;
}
    
int do_UserThreadExit() {
    return 0;
}
/*
void UserThreadExit() {
  
}
*/
void StartUserThread(int f) {
    //To compile
    //struct_user_thread* args;
    //args = (struct_user_thread*) f;
    
    currentThread->space->InitRegisters();
    currentThread->space->RestoreState();
    machine->Run();
}

#endif