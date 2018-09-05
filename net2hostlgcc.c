
#include <stdio.h>

void net2hostlgcc(long x)
{
	printf("\nOriginal Long: %08x\n", x);
	long newX = ((x>>24)&0xff) | ((x<<8)&0xff0000) | ((x>>8)&0xff00) | ((x<<24)&0xff000000);
	printf("New from C code: %08x\n", newX);
}