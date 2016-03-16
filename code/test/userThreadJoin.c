#include "syscall.h"
#include "stdio.h"

void test(void* arg) {
    //PutInt(*((int*)arg));
    PutString(" - beginning\n");
  
    int a;
    if (arg > 0)
        a = *((int*)arg)+1;
    else
        a = 1;
   
    int i;
    for (i=0; i < 10000*a;)
        i=i+1;

    //PutInt(*((int*)arg));
    PutString(" - exiting\n");
    
    if (arg > 0) {
         PutInt(*((int*)arg));
        PutString(" - joining\n");
        UserThreadJoin(*((int*)arg));
    }
    
    UserThreadExit();
}

int main() {
    int tId1, tId2;
    
    PutString("Début du main\n");
    tId1 = UserThreadCreate(test, 0);
    
    int i;
    for (i=0; i < 100000;)
        i=i+1;
    
    tId2 = UserThreadCreate(test, 0);
    
    PutString("Join\n");
    UserThreadJoin(tId1);

    return 2;
}

