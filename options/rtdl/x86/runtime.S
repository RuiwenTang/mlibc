
.global pltRelocateStub
pltRelocateStub:
	# we need to save / restore all registers than can hold function arguments
	# we do not need to save callee-saved registers as they will not be trashed by lazyRelocate
	# TODO: save floating point argument registers

	push %esi
	push %edi
	mov 8(%esp), %edi
	mov 12(%esp), %esi

	push %eax
	push %ecx
	push %edx

	call lazyRelocate
	# mov %rax, %r11

	pop %edx
	pop %ecx
	pop %eax
	
	pop %edi
	pop %esi
	add $8, %esp
	jmp *%eax # this is wrong

.section .note.GNU-stack,"",%progbits

