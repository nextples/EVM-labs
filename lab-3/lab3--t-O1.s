	.file	"main.c"
	.text
	.globl	swap
	.type	swap, @function
swap:
.LFB39:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE39:
	.size	swap, .-swap
	.globl	FillArray
	.type	FillArray, @function
FillArray:
.LFB40:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbp
	movl	$4, %esi
	call	calloc@PLT
	movq	%rax, %r12
	testq	%rbp, %rbp
	jle	.L2
	movl	$0, %ebx
.L4:
	call	rand@PLT
	movslq	%eax, %rdx
	imulq	$274877907, %rdx, %rdx
	sarq	$38, %rdx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	imull	$1000, %edx, %edx
	subl	%edx, %eax
	movl	%eax, (%r12,%rbx,4)
	addq	$1, %rbx
	cmpq	%rbx, %rbp
	jne	.L4
.L2:
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE40:
	.size	FillArray, .-FillArray
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$140000, %edi
	call	FillArray
	movq	%rax, %r8
	movl	$140000, %edi
	leaq	559996(%rax), %rsi
	jmp	.L8
.L9:
	addq	$4, %rax
	cmpq	%rsi, %rax
	je	.L14
.L10:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L9
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
	jmp	.L9
.L14:
	subl	$1, %edi
	je	.L11
.L8:
	movq	%r8, %rax
	jmp	.L10
.L11:
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE41:
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
