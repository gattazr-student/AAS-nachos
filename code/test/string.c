#include "syscall.h"

int main() {
    unsigned int size = 80;
    char str[80];

    /* Read a string and print it */
    GetString(str, size);

    // Exit if the string is empty
    while(str[0] != '\0'){
        // Print the string
        PutString(str);
        GetString(str, size);
    }
    PutChar('\n');
    Halt();
}
