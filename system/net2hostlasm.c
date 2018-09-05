#include <xinu.h>
#include <stdio.h>

void net2hostlasm(long x) 
{
	asm("mov 4(%esp), %eax\n\t" 
		"bswap %eax\n\t"
		"ret");
}