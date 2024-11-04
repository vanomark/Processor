	.file	"ASSEMBLER.cpp"
	.text
	.section	.rodata
	.align 8
	.type	_ZL7MAX_CMD, @object
	.size	_ZL7MAX_CMD, 8
_ZL7MAX_CMD:
	.quad	100
	.align 8
	.type	_ZL12MIN_STR_SIZE, @object
	.size	_ZL12MIN_STR_SIZE, 8
_ZL12MIN_STR_SIZE:
	.quad	50
.LC0:
	.string	"PROGRAM_CODE.txt"
.LC1:
	.string	"PROGRAM_ASM.txt"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	_Z6RunASSPKcS0_
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC2:
	.string	"r"
.LC3:
	.string	"Null pointer\n"
.LC4:
	.string	"w"
	.align 8
.LC5:
	.string	"int RunASS(const char*, const char*)"
.LC6:
	.string	"src/ASSEMBLER.cpp"
.LC7:
	.string	"out_file"
.LC8:
	.string	"NEFORSKAYA DURKA\n"
.LC9:
	.string	"%s"
.LC10:
	.string	"push"
.LC11:
	.string	"%d"
.LC12:
	.string	"%d %d "
.LC13:
	.string	"add"
.LC14:
	.string	"%d "
.LC15:
	.string	"sub"
.LC16:
	.string	"mul"
.LC17:
	.string	"div"
.LC18:
	.string	"out"
.LC19:
	.string	"jmp"
.LC20:
	.string	"hlt"
.LC21:
	.string	"Syntax error\n"
.LC22:
	.string	"YA PO ZHIZNY ZDRAVIY PATSAN\n"
	.text
	.globl	_Z6RunASSPKcS0_
	.type	_Z6RunASSPKcS0_, @function
_Z6RunASSPKcS0_:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$512, %rsp
	movq	%rdi, -504(%rbp)
	movq	%rsi, -512(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -488(%rbp)
	movq	-504(%rbp), %rax
	leaq	.LC2(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -488(%rbp)
	cmpq	$0, -488(%rbp)
	sete	%al
	testb	%al, %al
	je	.L4
	leaq	.LC2(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -488(%rbp)
.L4:
	cmpq	$0, -488(%rbp)
	jne	.L5
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$13, %edx
	movl	$1, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, %eax
	jmp	.L20
.L5:
	movq	-512(%rbp), %rax
	leaq	.LC4(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -472(%rbp)
	cmpq	$0, -472(%rbp)
	jne	.L7
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	movl	$24, %edx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L7:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$17, %edx
	movl	$1, %esi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	leaq	-464(%rbp), %rdx
	movl	$0, %eax
	movl	$50, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	$0, -480(%rbp)
	jmp	.L8
.L19:
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movw	$0, -16(%rbp)
	leaq	-64(%rbp), %rdx
	movq	-488(%rbp), %rax
	leaq	.LC9(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	leaq	-64(%rbp), %rax
	leaq	.LC10(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L9
	movl	$0, -492(%rbp)
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$1, -464(%rbp,%rax,4)
	leaq	-492(%rbp), %rdx
	movq	-488(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	movl	-492(%rbp), %edx
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -480(%rbp)
	movl	%edx, -464(%rbp,%rax,4)
	movl	-492(%rbp), %edx
	movq	-472(%rbp), %rax
	movl	%edx, %ecx
	movl	$1, %edx
	leaq	.LC12(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L8
.L9:
	leaq	-64(%rbp), %rax
	leaq	.LC13(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L11
	movq	-472(%rbp), %rax
	movl	$2, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$2, -464(%rbp,%rax,4)
	jmp	.L8
.L11:
	leaq	-64(%rbp), %rax
	leaq	.LC15(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L12
	movq	-472(%rbp), %rax
	movl	$3, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$3, -464(%rbp,%rax,4)
	jmp	.L8
.L12:
	leaq	-64(%rbp), %rax
	leaq	.LC16(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L13
	movq	-472(%rbp), %rax
	movl	$4, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$4, -464(%rbp,%rax,4)
	jmp	.L8
.L13:
	leaq	-64(%rbp), %rax
	leaq	.LC17(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L14
	movq	-472(%rbp), %rax
	movl	$5, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$5, -464(%rbp,%rax,4)
	jmp	.L8
.L14:
	leaq	-64(%rbp), %rax
	leaq	.LC18(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L15
	movq	-472(%rbp), %rax
	movl	$6, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$6, -464(%rbp,%rax,4)
	jmp	.L8
.L15:
	leaq	-64(%rbp), %rax
	leaq	.LC19(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L16
	movl	$0, -492(%rbp)
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$8, -464(%rbp,%rax,4)
	movl	-492(%rbp), %edx
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -480(%rbp)
	movl	%edx, -464(%rbp,%rax,4)
	leaq	-492(%rbp), %rdx
	movq	-488(%rbp), %rax
	leaq	.LC11(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	movl	-492(%rbp), %edx
	movq	-472(%rbp), %rax
	movl	%edx, %ecx
	movl	$8, %edx
	leaq	.LC12(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	jmp	.L8
.L16:
	leaq	-64(%rbp), %rax
	leaq	.LC20(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L17
	movq	-472(%rbp), %rax
	movl	$0, %edx
	leaq	.LC14(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movq	-480(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -480(%rbp)
	movl	$0, -464(%rbp,%rax,4)
	jmp	.L18
.L17:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$13, %edx
	movl	$1, %esi
	leaq	.LC21(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	$100, -480(%rbp)
.L8:
	cmpq	$99, -480(%rbp)
	jbe	.L19
.L18:
	movq	-488(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$28, %edx
	movl	$1, %esi
	leaq	.LC22(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	$0, %eax
.L20:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z6RunASSPKcS0_, .-_Z6RunASSPKcS0_
	.section	.rodata
.LC23:
	.string	"size_t tell_file_size(FILE*)"
.LC24:
	.string	"fp"
	.text
	.globl	_Z14tell_file_sizeP8_IO_FILE
	.type	_Z14tell_file_sizeP8_IO_FILE, @function
_Z14tell_file_sizeP8_IO_FILE:
.LFB2:
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
	jne	.L23
	leaq	.LC23(%rip), %rax
	movq	%rax, %rcx
	movl	$103, %edx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC24(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L23:
	movq	-24(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	_Z14tell_file_sizeP8_IO_FILE, .-_Z14tell_file_sizeP8_IO_FILE
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
