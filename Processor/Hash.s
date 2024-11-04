	.file	"Hash.cpp"
	.text
	.section	.rodata
	.align 8
	.type	_ZL8MIN_SIZE, @object
	.size	_ZL8MIN_SIZE, 8
_ZL8MIN_SIZE:
	.quad	8
	.align 8
	.type	_ZL8MAX_SIZE, @object
	.size	_ZL8MAX_SIZE, 8
_ZL8MAX_SIZE:
	.quad	4000000
	.align 8
	.type	_ZL5CANLA, @object
	.size	_ZL5CANLA, 8
_ZL5CANLA:
	.quad	3405691582
	.align 8
	.type	_ZL5CANRA, @object
	.size	_ZL5CANRA, 8
_ZL5CANRA:
	.quad	4276215469
	.align 8
	.type	_ZL5CANLS, @object
	.size	_ZL5CANLS, 8
_ZL5CANLS:
	.quad	3131961357
	.align 8
	.type	_ZL5CANRS, @object
	.size	_ZL5CANRS, 8
_ZL5CANRS:
	.quad	1017641678
.LC0:
	.string	"hash_t gon1(Stack*)"
.LC1:
	.string	"src/Hash.cpp"
.LC2:
	.string	"Stk"
	.text
	.globl	_Z4gon1P5Stack
	.type	_Z4gon1P5Stack, @function
_Z4gon1P5Stack:
.LFB15:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L2
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	movl	$5, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L2:
	movq	$228, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rdx, %rax
	addq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	addq	%rdx, %rax
	addq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	imulq	$1488, %rax, %rax
	subq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	_Z4gon1P5Stack, .-_Z4gon1P5Stack
	.section	.rodata
	.align 8
.LC3:
	.string	"hash_t djb2(const void*, size_t)"
.LC4:
	.string	"data"
	.text
	.globl	_Z4djb2PKvm
	.type	_Z4djb2PKvm, @function
_Z4djb2PKvm:
.LFB16:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L5
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	movl	$19, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L5:
	movq	$5381, -16(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L6
.L7:
	movq	-8(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltq
	addq	%rax, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	%rdx, %rax
	salq	$5, %rax
	subq	%rdx, %rax
	movq	%rax, %rcx
	movq	-8(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cltq
	xorq	%rcx, %rax
	movq	%rax, -16(%rbp)
	addq	$1, -8(%rbp)
.L6:
	movq	-8(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jb	.L7
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	_Z4djb2PKvm, .-_Z4djb2PKvm
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
