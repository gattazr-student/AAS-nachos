#include "syscall.h"
#include "stdio.h"

void test(void * arg) {
    PutString("test\n");
    UserThreadExit();
}

int main() {
	int i;
    PutString("Début du main\n");
    for(i=1;i<3;i++)
    	UserThreadCreate(test, 0);

    PutString("Fin du main\n");

    Halt();
}
