#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

struct struct_user_thread
{
    int f;
    int arg;
};

int do_UserThreadCreate(int f, int arg);

int do_UserThreadExit();

void StartUserThread(int f);

#endif
#endif
