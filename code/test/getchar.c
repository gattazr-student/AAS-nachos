#include "syscall.h"
#include "stdio.h"

int main() {
    char c;
    /* Read a char and print it */
    c = GetChar();
    while(c != EOF){
        PutChar(c);
        c = GetChar();
    }
    PutChar('\n');
    Halt();
}
