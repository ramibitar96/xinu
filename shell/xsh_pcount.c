/* xsh_pcount.c - xsh_pcount */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_pscount - shell command to print the total number of processes
 *------------------------------------------------------------------------
 */
shellcmd xsh_pcount(int nargs, char *args[])
{
	struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into proctabl		*/
	int count = 0;

	/* For argument '--help', emit help about the 'ps' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays number of processes\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate == PR_FREE) {  /* skip unused slots	*/
			continue;
		}
		count++;
	}
	printf(" there are currently %d processes\n", count);
	return 0;	
}