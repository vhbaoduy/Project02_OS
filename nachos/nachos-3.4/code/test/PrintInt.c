#include "syscall.h"
#include "copyright.h"
int main()
{
	int n;
	PrintString("Nhap 1 so:");
	n = ReadInt();
	PrintString("So vua nhap:");
	PrintInt(n); // Test the PrintInt function: print 100 to console.
	return 0;
}
