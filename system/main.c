#include <xinu.h>

process TA_proc1 (void) {

	while(1) {
		;
	}
	return OK;
}

process main(void) {
	//Test create 1 process, sleeps for 4 seconds, then create 2nd process.
	//The prcpuused of second process should be average of all other processes

	pid32   p1, p2;

	p1 = create(TA_proc1, 1024, 1, "TA_Proc1 1", 0);

	//should print prcpuused very small
	kprintf("\nP1 created with prcpuused: %d. Time: %d\n", 
		proctab[p1].prcpuused, clktimefine);

	resume(p1);
	sleep(6);

	p2 = create(TA_proc1, 1024, 1, "TA_Proc1 2", 0);
	//should print around 6000/2 for pr2
	kprintf("\nMain woke after 6 seconds sleep\n");	
	kprintf("P1 has prcpuused: %d\n", proctab[p1].prcpuused);
	kprintf("\nP2 created with prcpuused: %d. Time: %d\n", 
		proctab[p2].prcpuused,  clktimefine);

	resume(p2);
	sleep(2);

	kprintf("\nMain wakes up after 2 sec. Time: %d\n", clktimefine);
	kprintf("P1 CPU Usage: %d\n", proctab[p1].prcpuused);
	kprintf("P2 CPU Usage: %d\n", proctab[p2].prcpuused);

	kill(p1);
	kill(p2);

	return OK;
}
