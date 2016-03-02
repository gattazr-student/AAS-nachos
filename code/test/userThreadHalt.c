#include "syscall.h"
#include "stdio.h"

void test(void* arg) {
    //PutString("test\n");
    //PutInt(*((int*)arg));
    int a = *((int*)arg);
    int i;
    for (i=0; i < 1000*a;)
        i=i+1;
    
    //PutString("exiting\n");
    //PutInt(*((int*)arg));
    UserThreadExit();
}

int main() {
    //PutString("Début du main\n");
    int i;
    int b = 1;
    for (i=0; i < 5; i++)
        UserThreadCreate(test, &b);
    
    //int a = 1;
   // int b = 2;
    int c = 300;
    
    //UserThreadCreate(test, &b);
    UserThreadCreate(test, &c);
   
    //PutString("Fin du main\n");
    Halt();
}
