#include <xinu.h>
#include <stdio.h>

void stacksmashV()
{
	char v = 'V';
	putc(CONSOLE, v);
}