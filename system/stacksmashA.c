#include <xinu.h>
#include <stdio.h>

void takeover() 
{
	printf("Takeover Succeeded\n");
	printf("Takeover Succeeded\n");
	printf("Takeover Succeeded\n");
	printf("Takeover Succeeded\n");
	printf("Takeover Succeeded\n");
	printf("Takeover Succeeded\n");
	return;
}

void stacksmashA() 
{
	int i = 0;
	int size = 1024;
	volatile int takeoverArray[size];
	while (i < size) 
	{
		takeoverArray[i] = &takeover;
		i++;
	}
}

