
.section .text
.global _start
_start:
    mov $main, %edi
    push %edi
    call __mlibc_entry

.section .note.GNU-stack,"",%progbits
