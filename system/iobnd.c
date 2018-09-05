#include <xinu.h>

void iobnd(void) 
{
	struct procent *pt;
	int i = 0;
	int j = 0;
	pt = &proctab[currpid];
	for (i=0; i <= 100; i++) {
  		for (j=0; j <= 10; j++) {
    		// Insert code that performs memory copy (slow) and/or
    		// ALU operations (fast).
    		// Note: this loop consumes significant CPU cycles.
    		sleepms(5);
  		}
  		// Using kprintf, print the pid followed by the outer loop count i,
  		// the process's priority, and the remaining time slice (preempt).
	}
	kprintf("\n pid: %d usage: %d \n", currpid, pt->prcpuused);
	if (currpid == 6)
		kprintf("\nclktimefine: %d\n", clktimefine);
	// Print the CPU time consumed by the process that is recorded in the
	// prcpuused field of the current process's process table entry.
}