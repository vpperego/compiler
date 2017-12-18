
.globl d
.data
.align 4
.type d, @object
.size d, 4
d:
.long 65
.globl main
.type main, @function
main:
.LFB1:
.cfi_startproc
pushq	%rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq	%rsp, %rbp
.cfi_def_cfa_register 6

call	printf
popq	%rbp
.cfi_def_cfa 7, 8
ret
.cfi_endproc
.LFE1:
.size	main, .-main
