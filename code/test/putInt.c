#include "syscall.h"

void print(int i, int n)
{
    int j;
    for (j = 0; j < n; j++) {
        PutInt(i+j);
        PutChar('-');
    }
    PutInt(i+j);
    PutChar('\n');
}
int main() {
    print(0,1000);
    Halt();
}
