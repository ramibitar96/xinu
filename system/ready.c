/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	heapinsert(pid, prptr->prcpuused);
	// kprintf("\nIM IN READY\n");
	// kprintf("\nPid is being put  into the readylist %s\n", prptr->prname);
	total_ready_proc += 1;
	// kprintf("\nhi inside ready %d %d\n", pid ,total_ready_proc);
	total_cpu_usage += prptr->prcpuused;

	

	// int16 curr;
	// curr = firstid(readylist);
	// while(queuetab[curr].qkey != MAXKEY) {
	// 	kprintf("%d %d\n", curr ,queuetab[curr].qkey);
	// 	curr = queuetab[curr].qnext;
	// }

	resched();

	return OK;
}
