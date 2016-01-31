#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console(readFile, writeFile, ReadAvail, WriteDone, 0);
}
SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
}
void SynchConsole::SynchPutChar(const char ch)
{
    console->PutChar(ch);	// echo it!
    writeDone->P();	// wait for write to finish
}

char SynchConsole::SynchGetChar()
{
    readAvail->P(); // wait for character to arrive
    return console->GetChar ();
}

void SynchConsole::SynchPutString(const char s[])
{
    int i;
    for(i=0; s[i]!='\0'; i++) {
        this->SynchPutChar(s[i]);
    }
}

/**
 * Read a string until EOF or \n is found. Read n-1 char at most
 */
void SynchConsole::SynchGetString(char *s, int n)
{
    int i = 0;
    while( i < n-1) {
        s[i] = this->SynchGetChar();

        /* We stop reading at \n or EOF (not kept) */
        if(s[i] == '\n' || s[i] == EOF){
            break;
        }
        i++;
    }
    s[i] = '\0';
}
#endif // CHANGED
