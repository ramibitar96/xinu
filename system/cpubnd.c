#include <xinu.h>

void cpubnd(void) 
{
	struct procent *pt;
	int i = 0;
	int j = 0;
	int k = 0;

	pt = &proctab[currpid];

	for (i=0; i <= 100000; i++) {
  		for (j=0; j <= 10000; j++) {
    		// Insert code that performs memory copy (slow) and/or
    		// ALU operations (fast).
    		// Note: this loop consumes significant CPU cycles.
  			k = i + j;
  			k = k + k;
  			k = k*2;
  			k = k/2;
  			k = k - k;
  			k = k + 100;
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