#include "syscall.h"
#include "copyright.h"
int main()
{
	char str[100];
	PrintString("Nhap 1 chuoi:");
	ReadString(str,100);
	PrintString("Chuoi vua nhap:");
	PrintString(str);
}
