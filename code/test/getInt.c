#include "syscall.h"
#include "stdio.h"

int main() {
    int i;
    /* Read an int and prints it */
    i = 2;
    GetInt(&i);

    while(i > 0){
        PutInt(i);
        PutChar('\n');
        GetInt(&i);
    }
    PutInt(i);
    PutChar('\n');
    Halt();
}
