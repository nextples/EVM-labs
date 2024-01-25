	.file	"main.c"
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB24:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE24:
	.size	swap, .-swap
	.globl	FillArray
	.type	FillArray, @function
FillArray:
.LFB25:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$4, %esi
	movl	$1000, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebx, %ebx
	pushq	%rcx
	.cfi_def_cfa_offset 48
	call	calloc@PLT
	movq	%rax, %r12
.L3:
	cmpq	%rbx, %rbp
	jle	.L7
	call	rand@PLT
	cltd
	idivl	%r13d
	movl	%edx, (%r12,%rbx,4)
	incq	%rbx
	jmp	.L3
.L7:
	popq	%rdx
	.cfi_def_cfa_offset 40
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	FillArray, .-FillArray
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	endbr64
	pushq	%rcx
	.cfi_def_cfa_offset 16
	movl	$140000, %edi
	call	FillArray
	movl	$140000, %ecx
	leaq	559996(%rax), %r8
.L9:
	movq	%rax, %rdx
.L11:
	movl	(%rdx), %esi
	movl	4(%rdx), %edi
	cmpl	%edi, %esi
	jle	.L10
	movl	%edi, (%rdx)
	movl	%esi, 4(%rdx)
.L10:
	addq	$4, %rdx
	cmpq	%r8, %rdx
	jne	.L11
	decl	%ecx
	jne	.L9
	xorl	%eax, %eax
	popq	%rdx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
