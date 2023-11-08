	.file	"ex-mm-daxpy.c"
	.text
	.globl	matmul
	.type	matmul, @function
matmul:
.LFB0:
	.cfi_startproc
	endbr64
	testq	%rcx, %rcx
	jle	.L11
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rsi, %r8
	movq	%rdx, %r10
	movq	%rcx, %r12
	movq	%rcx, %r11
	leaq	0(,%rcx,8), %rbx
	addq	%rbx, %r8
	movq	%rdi, %r9
	leaq	(%rdi,%rbx), %rsi
	movq	%rcx, %r13
	negq	%r13
	salq	$3, %r13
	movl	$0, %ebp
	jmp	.L3
.L14:
	addq	$8, %rcx
	addq	%r11, %rdi
	cmpq	%r8, %rcx
	je	.L7
.L5:
	leaq	(%r10,%rdi,8), %rdx
	movq	%r9, %rax
.L6:
	movsd	(%rcx), %xmm0
	mulsd	(%rdx), %xmm0
	addsd	(%rax), %xmm0
	movsd	%xmm0, (%rax)
	addq	$8, %rax
	addq	$8, %rdx
	cmpq	%rsi, %rax
	jne	.L6
	jmp	.L14
.L7:
	addq	$1, %rbp
	addq	%rbx, %r8
	addq	%rbx, %r9
	addq	%rbx, %rsi
	cmpq	%rbp, %r12
	je	.L1
.L3:
	movq	%r9, %rax
.L4:
	movq	$0x000000000, (%rax)
	addq	$8, %rax
	cmpq	%rsi, %rax
	jne	.L4
	leaq	(%r8,%r13), %rcx
	movl	$0, %edi
	jmp	.L5
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE0:
	.size	matmul, .-matmul
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
