#include "syscall.h"

int main() {
    unsigned int size = 80;
    char str[80];
    int i;

    /* Read a string and print it */
    GetString(str, size);

    // Exit if the string is empty
    while(str[0] != '\0'){
        // Print the string
        for(i=0; i < size && str[i] != '\0'; i++){
            PutChar(str[i]);
        }
        GetString(str, size);
    }
    PutChar('\n');
    Halt();
}
