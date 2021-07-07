// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
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

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

// -------------------------------------------
// Doi thanh dang switch 
// Xu li cac truong hop runtime
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch(which)
    {
	// Tra quyen ve cho he dieu hanh
	case NoException:
		return;

	// In ra thong bao loi cho nguoi dung
	// ->Dung he thong
	case PageFaultException:
		interrupt->Halt();
		break;
	case ReadOnlyException:
		interrupt->Halt();
		break;
	case BusErrorException:
		interrupt->Halt();
		break;
	case AddressErrorException:
		interrupt->Halt();
		break;
	case OverflowException:
		interrupt->Halt();
		break;
	case IllegalInstrException:
		interrupt->Halt();
		break;
	case NumExceptionTypes:
		interrupt->Halt();
		break;
	case SyscallException:
		switch(type)
			case SC_Halt:
			{
				DEBUG('a', "\nShutdown, initiated by user program. ");
				printf("\nShutdown, initiated by user program. ");
				interrupt->Halt();
				return;
			}
			// test SC_Sub
			case SC_Sub:
			{
				int op1,op2,result;
				op1 = machine->ReadRegister (4); 
				op2 = machine->ReadRegister (5); 
				result = op1 - op2; 
				machine->WriteRegister (2, result);
				printf("\nSub is tested");
			}
			
		machine->IncreaseProgramCounter();
		break;

    }
/*
	
    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
*/
}