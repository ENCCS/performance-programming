	.file	"add.c"
	.text
	.p2align 4
	.globl	add
	.type	add, @function
add:
.LFB0:
	.cfi_startproc
	endbr64
	testl	%edx, %edx
	jle	.L9
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%r11d, %r11d
	movl	%edx, %ebx
	leal	-1(%rcx), %r10d
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L3:
	testl	%ecx, %ecx
	jle	.L6
	movslq	%edx, %rax
	leaq	(%rdi,%rax,8), %r8
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movsd	(%r8,%rax,8), %xmm0
	addsd	(%rsi,%rax,8), %xmm0
	movq	%rax, %r9
	movsd	%xmm0, (%r8,%rax,8)
	addq	$1, %rax
	cmpq	%r9, %r10
	jne	.L4
.L6:
	addl	$1, %r11d
	addl	%ecx, %edx
	cmpl	%r11d, %ebx
	jne	.L3
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
