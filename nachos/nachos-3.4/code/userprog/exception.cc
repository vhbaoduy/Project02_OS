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
#define MAX_INT_LENGTH 11
#define MAX_BUFFER 255
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
		DEBUG('a', "\nNo valid translation found");
		printf("\nNo valid translation found");
		interrupt->Halt();
		break;
	case ReadOnlyException:
		DEBUG('a', "\nWrite attempted to page marked read-only");
		printf("\nWrite attempted to page marked read-only");
		interrupt->Halt();
		break;
	case BusErrorException:
		DEBUG('a', "\nTranslation resulted in an invalid physical address");
		printf("\nTranslation resulted in an invalid physical address");
		interrupt->Halt();
		break;
	case AddressErrorException:
		DEBUG('a', "\nUnaligned reference or one that was beyond the end of the  address space");
		printf("\nUnaligned reference or one that was beyond the end of the  address space");
		interrupt->Halt();
		break;
	case OverflowException:
		DEBUG('a', "\nInteger overflow in add or sub.");
		printf("\nInteger overflow in add or sub.");
		interrupt->Halt();
		break;
	case IllegalInstrException:
		DEBUG('a', "\nUnimplemented or reserved instr.");
		printf("\nUnimplemented or reserved instr.");
		interrupt->Halt();
		break;
	case NumExceptionTypes:
		DEBUG('a', "\nNumber Exception Types");
		printf("\nNumber Exception Types");
		interrupt->Halt();
		break;
	case SyscallException:
		switch(type)
		{
			case SC_Halt:
			{
				DEBUG('a', "\nShutdown, initiated by user program. ");
				printf("\nShutdown, initiated by user program. ");
				interrupt->Halt();
				return;
			}

			case SC_ReadInt:
			{

				//Read integer number and return it
				DEBUG('a', "Read integer number from console.\n");
				int number = 0;
				int nDigit = 0;
				int i;
				char MAX_INT[] = "2147483647";
				//MAX_INT = "2147483647";

				char MIN_INT[] = "-2147483648";
				//MIN_INT = "-2147483648";

				char* buffer = new char[MAX_BUFFER];
				nDigit = gSynchConsole->Read(buffer, MAX_BUFFER);
				i = buffer[0] == '-' ? 1:0 ;
				int firstNumIndex = i;
                    		int lastNumIndex = i;     

                    		// Kiem tra tinh hop le cua so nguyen buffer
                    		for(; i < nDigit; i++)					
                    		{
                        		if(buffer[i] == '.') /// 125.0000000 van la so
                        		{
                            			int j = i + 1;
                           			for(; j < nDigit; j++)
                            			{
							// So khong hop le
                                			if(buffer[j] != '0') // Phan thap phan khac 0 la khong hop le
                                			{
                                    				printf("\nThe integer number is not valid\n");
                                    				DEBUG('a', "\n The integer number is not valid");
                                    				machine->WriteRegister(2, 0);
                                   				machine->IncreaseProgramCounter();
                                    				delete[] buffer;
                                    				return;
                                			}
                            			}
                        
                            			lastNumIndex = i - 1;				
                            			break;                           
                        		}
                        		else if(buffer[i] < '0' || buffer[i] > '9') // Khong phai la so
                        		{
                            			printf("\nThe integer number is not valid\n");
                            			DEBUG('a', "\n The integer number is not valid");
                            			machine->WriteRegister(2, 0);
                            			machine->IncreaseProgramCounter();
                                    		delete[] buffer;
                                    		return;
                        		}
                        		lastNumIndex = i;    
                    		}
				// Kiem tra co nam trong khoang tu MIN_INT den MAX_INT
				if ((buffer[0] == '-' && lastNumIndex > 10) || (buffer[0] != '-' && lastNumIndex > 9))
				{
					printf("\nThe integer number is not valid\n");
                                    	DEBUG('a', "\n The integer number is not valid");
                                    	machine->WriteRegister(2, 0);
                                   	machine->IncreaseProgramCounter();
                                    	delete[] buffer;
                                    	return;
				}
                    		else if (buffer[0] == '-' && lastNumIndex == 10)
				{	
					for(i = 1; i<= lastNumIndex; i++)
                    			{
						if (buffer[i] > MIN_INT[i])
						{
							printf("\nThe integer number is not valid\n");
                                    			DEBUG('a', "\n The integer number is not valid");
                                    			machine->WriteRegister(2, 0);
                                   			machine->IncreaseProgramCounter();
                                    			delete[] buffer;
                                    			return;
						}
                    			}
				}
				else if (buffer[0] != '-' && lastNumIndex == 9)
				{
					for(i = 0; i<= lastNumIndex; i++)
                    			{
                        			if (buffer[i] > MAX_INT[i])
						{
							printf("\nThe integer number is not valid\n");
                                    			DEBUG('a', "\n The integer number is not valid");
                                    			machine->WriteRegister(2, 0);
                                   			machine->IncreaseProgramCounter();
                                    			delete[] buffer;
                                    			return;
						}
                    			}
				}
                    		// So nguyen hop le
                    		for(i = firstNumIndex; i<= lastNumIndex; i++)
                    		{
                        		number = number * 10 + (int)(buffer[i] - '0'); 
                    		}
				number = buffer[0] == '-' ? -1*number : number;
				machine->WriteRegister(2, number);
				delete[] buffer;
			}
			break;

			case SC_PrintInt:
			{
				char s[11], neg, tmp;
				neg = '-';
				int i, mid, len;
				long long n;
				i = n = 0;
				DEBUG('a', "Read argument value at r4");
				n = machine->ReadRegister(4);
				if (n < 0)
				{
					gSynchConsole->Write("-",1);
					n = -n;
				}
				do {
					s[i++] = n%10 + '0';
				}while (( n /= 10) > 0);
				len = i;
				s[len] = '\n';
				mid = i / 2;
				while (i-- > mid)
				{
					tmp = s[len-i-1];
					s[len-i-1] = s[i];
					s[i] = tmp;
				}
				gSynchConsole->Write(s, len);
			}
			break;
			case SC_ReadChar:
			{
				char* buffer= new char[MAX_BUFFER];
				int num_bytes=gSynchConsole->Read(buffer,MAX_BUFFER);
				machine->WriteRegister(2, char(buffer[0]));
				delete[] buffer;
			}
			break;
			case SC_PrintChar:
			{
				char ch = (char)machine->ReadRegister(4);
				gSynchConsole->Write(&ch,1); //In ky tu ra man hinh
			}
			break;
			case SC_ReadString:
			{
				char* buffer=new char[MAX_BUFFER];
				int virtAddr=machine->ReadRegister(4);
				int length=machine->ReadRegister(5);
				int sz=gSynchConsole->Read(buffer,length);
				machine->System2User(virtAddr,sz,buffer);
				delete[] buffer;
			}
			break;
			case SC_PrintString:
			{
				char* buffer=new char[MAX_BUFFER];
				int virtAddr=machine->ReadRegister(4), length=0;
				buffer = machine-> User2System(virtAddr, MAX_BUFFER); 
				while (buffer[length] != 0 && buffer[length] != '\n')
				{
					gSynchConsole->Write(buffer+length, 1);
					length++;
				}
				buffer[length] = '\n';
				gSynchConsole->Write(buffer+length,1); //In chuoi ra man hinh
				delete[] buffer;
			}
			break;
			// test SC_Sub
			case SC_Sub:
			{
				int op1,op2;
				op1 = machine->ReadRegister (4); 
				op2 = machine->ReadRegister (5); 
				int result = op1 - op2; 
				printf("\nSub is tested");
				machine->WriteRegister (2, result);
			}
			break;
		}

		// Tang program Counter de chuong trinh khong bi lap vo han	
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
