#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

struct struct_user_thread
{
    int f;
    int arg;
    int callback;
};

int do_UserThreadCreate(int f, int arg, int callback);

int do_UserThreadExit();

/*
* returns -1: when thread does not exist anymore
* returns -2: when thread has been replaced (the wanted one does not exist anymore)
* returns  0: join successed
*/
int do_UserThreadJoin(int Id);

void StartUserThread(int f);

#endif
#endif
