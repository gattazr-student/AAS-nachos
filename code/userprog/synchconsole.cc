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

    semRead = new Semaphore("console read avail", 1);
    semWrite = new Semaphore("console write avail", 1);
}
SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;

    delete semRead;
    delete semWrite;
}

void SynchConsole::SynchPutChar(const char ch)
{
    semWrite->P();
    console->PutChar(ch);	// echo it!
    writeDone->P();	// wait for write to finish
    semWrite->V();
}

int SynchConsole::SynchGetChar()
{
    int c;
    semRead->P();

    // ReadChar
    readAvail->P(); // wait for character to arrive
    c = (console->Feof())? EOF : (int)console->GetChar();

    semRead->V();
    return c;
}

void SynchConsole::SynchPutString(const char s[])
{
    int i;
    semWrite->P();

    // PutString
    for(i=0; s[i]!='\0'; i++) {
        // PutChar
        console->PutChar(s[i]);	// echo it!
        writeDone->P();	// wait for write to finish
    }

    semWrite->V();
}

/**
 * Read and create a string until EOF or \n is found. Read n-1 char at most.
 * if \n found, it is kept. EOF isn't.
 */
void SynchConsole::SynchGetString(char *s, int n)
{
    int i = 0;
    semRead->P();

    // GetString
    while(i < n-1) {
        // GetChar
        readAvail->P();
        s[i] = (console->Feof())? EOF : (int)console->GetChar();;

        /* We stop reading at \n or EOF */
        if(s[i] == '\n'){
            i++;
            break;
        }
        if((int)s[i] == EOF){
            break;
        }
        i++;
    }
    s[i] = '\0';

    semRead->V();
}

void SynchConsole::SynchPutInt(int i){
	char str[MAX_STRING_SIZE];

    snprintf(str, MAX_STRING_SIZE, "%d", i);
	this->SynchPutString(str);
}

void SynchConsole::SynchGetInt(int *i){
	char str[MAX_STRING_SIZE];
	this->SynchGetString(str, MAX_STRING_SIZE);
	*i=0;
    sscanf(str, "%d", i);
}
#endif // CHANGED
