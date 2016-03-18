#include "syscall.h"

/**
 * Pause a thread
 */
void pause_thread(void* arg) {
    int i;
    int wVal;
    wVal = *((int*)arg);
    PutString(" - beginning ");
    PutInt(wVal);
    PutChar('\n');

    for (i=0; i < 100000*wVal;)
        i=i+1;

    PutString(" - exiting ");
    PutInt(wVal);
    PutChar('\n');
    // Exit(2) // This exit should stop completly the programm
}

int main() {
    int i;
    int c[4];
    PutString("Begin of main\n");

    // Loop creating 4 threads
    PutString("Creating 5 threads\n");
    for (i=0; i < 5; i++){
        c[i] = i;
        UserThreadCreate(pause_thread, &(c[i]));
    }
    // Exit(1) // This exit should stop completly the programm

    PutString("end of main\n");
    // Halt() // This Halt should stop the programm when every threads are over
    return 9; // The return should call Halt(9) that will quit when all threads are over
}
