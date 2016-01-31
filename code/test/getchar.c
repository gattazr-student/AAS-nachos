#include "syscall.h"

int main() {
    char c;
    /* Read a char and print it */
    c = GetChar();
    PutChar(c);
    PutChar('\n');
    Halt();
}
