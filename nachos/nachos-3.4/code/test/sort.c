/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

int main()
{

	int temp, i,j, n;
	int a[100];
	PrintString("Nhap so phan tu mang (nho hon 100): ");
	n = ReadInt();
	PrintString("Nhap mang: ");
	for (i = 0; i < n; i++)
		a[i] = ReadInt();
    	for (i = 0; i < n-1; i++) 
	{ 
        	for (j = i+1; j < n; j++) 
            		if (a[j] < a[i])
			{
                		temp = a[j];
                		a[j] = a[i];
                		a[i] = temp;
            		} 
        }


	for (i = 0; i < n; i++)
	{
		PrintInt(a[i]);
		PrintChar(' ');
	}
	return 0;
}
