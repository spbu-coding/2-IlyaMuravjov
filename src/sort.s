	.file	"sort.c"
	.text
	.p2align 4,,15
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	testq	%rsi, %rsi
	je	.L1
	leaq	-8(%rdi,%rsi,8), %r8
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rdi, %rax
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	movq	(%rax), %rdx
	movq	8(%rax), %rcx
	cmpq	%rcx, %rdx
	jle	.L4
	movq	%rcx, (%rax)
	movq	%rdx, 8(%rax)
.L4:
	addq	$8, %rax
.L6:
	cmpq	%r8, %rax
	jne	.L5
	addq	$1, %r9
	cmpq	%r9, %rsi
	jne	.L3
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
