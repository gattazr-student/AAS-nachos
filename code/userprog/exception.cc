// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#ifdef CHANGED
#include "userthread.h"
#endif


#ifdef CHANGED
// ----
// Copy a string from the MIPS machine into the system
// ---
void
copyStringFromMachine(int from, char *to, unsigned size){
    unsigned read = 0;
    int readValue;

    while(read < size-1){
        machine->ReadMem(from + read, 1, &readValue);
        if(readValue == '\0'){
            break;
        }
        to[read] = (char) readValue;
        read++;
    }
    to[read] = '\0';
}

// ----
// Copy a string from the system to the MIPS machine
// ---
void
copyStringToMachine(char* from, int to, unsigned size){
    unsigned int written = 0;
    int nextChar;

    while(written < size-1){
        nextChar = (int)from[written];
        if(nextChar == EOF || nextChar == '\0'){
            break;
        }
        machine->WriteMem(to+written, 1, nextChar);
        written++;
    }
    machine->WriteMem(to+written, 1, '\0');
}
#endif


//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}

#ifdef CHANGED
void
do_system_call(int syscallNum)
{

    switch(syscallNum){
    case SC_Halt:
        DEBUG ('a', "Shutdown, initiated by user program.\n");
        interrupt->Halt ();
        break;

    case SC_GetChar:
        {
            int res;
            DEBUG('a', "Getchar syscall.\n");
            res = (int)synchconsole->SynchGetChar();
            machine->WriteRegister(2, res);
        }
        break;

    case SC_PutChar:
        {
            char c;
            DEBUG('a', "Putchar syscall.\n");
            c = (char)machine->ReadRegister(4);//retrieve the char in r4
            synchconsole->SynchPutChar(c);
        }
        break;

    case SC_GetString:
        {
            int strMips;
            int strSize;
            char *str;

            DEBUG('a', "GetString syscall.\n");
            strMips = (int)machine->ReadRegister(4);
            strSize = (int)machine->ReadRegister(5);
            str = new char[strSize];

            synchconsole->SynchGetString(str, strSize);
            copyStringToMachine(str, strMips, strSize);
            delete[] str;
        }
        break;

    case SC_PutString:
        {
            int strMips;
            char *str;
            DEBUG('a', "PutString syscall.\n");
            strMips = (int)machine->ReadRegister(4);
            str = new char[MAX_STRING_SIZE];

            copyStringFromMachine(strMips, str, MAX_STRING_SIZE);
            synchconsole->SynchPutString(str);
            delete[] str;
        }
        break;

    case SC_GetInt:
        {
            int i;
            int addr;
            DEBUG('a', "GetInt syscall.\n");
            /* a int* was given to getInt */
            addr = (int)machine->ReadRegister(4);
            synchconsole->SynchGetInt(&i);

            /* Use WriteMem to write i in mips memory at addr */
            machine->WriteMem(addr, sizeof(int), i);
        }
        break;

    case SC_PutInt:
        {
            int i;
            DEBUG('a', "PutInt syscall.\n");
            i = (int)machine->ReadRegister(4);

            synchconsole->SynchPutInt(i);
        }
        break;

    case SC_UserThreadCreate:
        {
            int ptr;
            int arg;
            int newThreadId;
            DEBUG('a', "UserThreadCreate syscall.\n");
            ptr = (int)machine->ReadRegister(4);
            arg = (int)machine->ReadRegister(5);
            newThreadId = do_UserThreadCreate(ptr, arg);
            if ( newThreadId == -1) {
                printf("Creation of new user thread failed.\n");
                ASSERT(FALSE);
            }else{
                /* Return the new thread id */
                machine->WriteRegister(2, newThreadId);
            }
        }
        break;

    case SC_UserThreadExit:
        {
            DEBUG('a', "UserThreadExit syscall.\n");

            do_UserThreadExit();
        }
        break;

    case SC_Exit:
        {
            int exitValue;
            DEBUG ('a', "Exit syscall.");
            exitValue = (int)machine->ReadRegister(4);
            Exit(exitValue);
        }
        break;

    default:
        printf ("Unknown exception %d\n", syscallNum);
        ASSERT (FALSE);
    }
}
#endif


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);

#ifdef CHANGED
    if (which == SyscallException)
      {
      do_system_call(type);
      }
#else
    if ((which == SyscallException) && (type == SC_Halt))
      {
      DEBUG ('a', "Shutdown, initiated by user program.\n");
      interrupt->Halt ();
      }
#endif
    else
      {
      printf ("Unexpected user mode exception %d %d\n", which, type);
      ASSERT (FALSE);
      }

    // LB: Do not forget to increment the pc before returning!
    UpdatePC ();
    // End of addition
}
