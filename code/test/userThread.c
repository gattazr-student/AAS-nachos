#include "syscall.h"
#include "stdio.h"

void test(void * arg) {
    PutString("test\n");
    UserThreadExit();
}

int main() {
    PutString("Début du main\n");
    UserThreadCreate(test, 0);
    
    char c = GetChar();
    PutChar(c);
    PutString("Fin du main\n");

    Halt();
}
