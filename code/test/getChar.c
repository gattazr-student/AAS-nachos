#include "syscall.h"
#include "stdio.h"

int main() {
    int c;
    /* Read a char and print it */
    c = GetChar();
    while(c != EOF){
        PutChar((char)c);
        c = GetChar();
    }
    PutChar('\n');
    Halt();
}
