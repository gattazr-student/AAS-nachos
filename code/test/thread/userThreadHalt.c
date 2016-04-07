#include "syscall.h"

void test(void* arg) {
    PutInt(*((int*)arg));
    PutString(" - beginning\n");
    int a = *((int*)arg);
    int i;
    for (i=0; i < 1000*a;)
        i=i+1;

    PutInt(*((int*)arg));
    PutString(" - exiting\n");
    // UserThreadExit();
}

int main() {
    int i;
    int c[4];
    PutString("Début du main\n");

    // Loop creating 4 threads
    for (i=0; i < 5; i++){
        c[i] = 10+i*10;
        UserThreadCreate(test, &(c[i]));
    }

    // Halt();
    return 2;
}
