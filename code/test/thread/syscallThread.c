#include "syscall.h"

void son(void *arg) {
    char c;

    PutString("Creation of 'son'\n");

    /* Working */
    PutString("Son waiting for char\n");
    c = GetChar();
    PutString("Char read ");
    PutChar(c);
    PutChar('\n');

    UserThreadExit();
}

int main() {

    PutString("Begin of main\n");
    int i = 1;
    do{
        UserThreadCreate(son, 0);
        i++;
    }while(i < 6);

    PutString("End of main\n");
    Halt();
}
