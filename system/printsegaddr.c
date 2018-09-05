#include <xinu.h>
#include <stdio.h>

void printsegaddr() 
{
	kprintf("\nLocations in order of: test, data, bss, end of bss\n");
	printf("Address of text: %08x\n", printsegaddr);
	long * numba0 = &printsegaddr;
	long * numba1 = &etext;
	long * numba2 = &data;
	long * numba3 = &end;
	printf("Address of data: %08x\n", numba1);
	printf("Address of bss start: %08x\n", numba2);
	printf("Address of bss end: %08x\n", numba3);
	*numba1++;
	*numba2++;
	*numba3++;
	int n = 4;
	int i = 0;

	for(; i < n; i++) {
		printf("%02X\n",numba0[i]);
		i++;
	}
	printf("\n");

	i = 0;
	for(; i < n; i++) {
		printf("%02X\n",numba1[i]);
		i++;
	}
	printf("\n");

	i = 0;
	for(; i < n; i++) {
		printf("%02X\n",numba2[i]);
		i++;
	}

	i = 0;
	printf("\n");
	for(; i < n; i++) {
		printf("%02X\n", numba3[i]);
		i++;
	}
	printf("\n");
	printf("Length of text is: %08x\n", (numba1 - numba0));
	printf("Length of data is: %08x\n", (numba2 - numba1));
	printf("Length of bss is: %08x\n", (numba3 - numba2));
}