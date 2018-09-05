/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	int32 difference;

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	// kprintf("\nIM IN RESCHED\n");
	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
	ptold->prcpuused += (clktimefine - ptold->prctxswstart);
	difference = clktimefine - ptold->prctxswstart;
	ptold->prctxswstart = clktimefine; 

	// kprintf("\n prname: %s prstate: %d \n", ptold->prname, ptold->prstate);

	if (ptold->prstate == PR_SLEEP && currpid != 0)
		total_cpu_usage -= ptold->prcpuused;

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible do not check if null proc here or error */
		if (ptold->prcpuused < heapminkey()) {
			// kprintf("\nfirstkey check %s %d %d\n", ptold->prname, ptold->prcpuused, firstkey(readylist));
			if (currpid != 0)
				total_cpu_usage += difference;
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
	
		// kprintf("\nPR CURR is being put back into the readylist %d\n", currpid);
		// kprintf("\ninserting %s\n" , ptold->prname);
		heapinsert(currpid, ptold->prcpuused);
		if(currpid != 0) {
			total_cpu_usage += difference;
			total_ready_proc += 1;

		}	
	}

	/* Force context switch to highest priority ready process */

	currpid = heapgethead();
	if (currpid == NULLPROC) {
		heapinsert(currpid, ptold->prcpuused);
		currpid = heapgethead();
	}
	// kprintf("\ncurrpid has dequeued %d\n", currpid);


	// 	int16 curr;
	// curr = firstid(readylist);
	// while(queuetab[curr].qkey != MAXKEY) {
	// 	kprintf("\nProcess ID: %d  Usage:%d\n", curr ,queuetab[curr].qkey);
	// 	curr = queuetab[curr].qnext;
	// }
	
	if (currpid != NULLPROC) {
		total_ready_proc -= 1;
	}
	



	ptnew = &proctab[currpid];
	// kprintf("\nold: %s new:%s\n", ptold->prname, ptnew->prname);
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ptnew->prctxswstart = clktimefine;
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
