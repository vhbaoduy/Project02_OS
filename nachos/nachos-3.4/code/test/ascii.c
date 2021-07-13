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

	int i = 32;
	for(; i < 127; i++)
	{
		PrintInt((int)i);
		PrintChar(':');
		PrintChar(i);
		PrintChar('\n');
	}
	return 0;

}
