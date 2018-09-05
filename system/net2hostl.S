/* net2hostl.S*/

/*------------------------------------------------------------------------
 * net2hostl  -  convert big endian to little endian
 *------------------------------------------------------------------------
 */

#include <icu.s>

	.text
	.globl net2hostl
net2hostl:
	mov 4(%esp), %eax 
	bswap %eax
	ret