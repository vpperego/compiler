	.globl	_444
	.data
	.type	_444, @object
	.size	_444, 4
_444:
	.long	444
	.globl	_a
	.data
	.type	_a, @object
	.size	_a, 4
_a:
	.long	444
	movl	_444(%rip), %eax
	movl	%eax, _a(%rip)
##TAC_BEGIN_FUN# 

	.globl main
	.type main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
##TAC_END_FUN# 
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	 .rodata
.LC2:
	.string "teste" 
