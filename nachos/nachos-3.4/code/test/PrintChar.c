#include "syscall.h"
#include "copyright.h"
int main()
{
	char ch;
	PrintString("Nhap 1 ky tu:");
	ch = ReadChar();
	PrintString("Ky tu vua nhap la:");
	PrintChar(ch);
}
