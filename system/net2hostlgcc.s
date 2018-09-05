	.file	"net2hostlgcc.c"
	.section	.rodata
.LC0:
	.string	"\nOriginal Long: %08x\n"
.LC1:
	.string	"New from C code: %08x\n"
	.text
	.globl	net2hostlgcc
	.type	net2hostlgcc, @function
net2hostlgcc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	8(%ebp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	sall	$8, %eax
	andl	$16711680, %eax
	orl	%eax, %edx
	movl	8(%ebp), %eax
	sarl	$8, %eax
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, -12(%ebp)
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	net2hostlgcc, .-net2hostlgcc
	.ident	"GCC: (Gentoo 4.9.3 p1.5, pie-0.6.4) 4.9.3"
	.section	.note.GNU-stack,"",@progbits
