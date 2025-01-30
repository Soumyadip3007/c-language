.section .text
.global _start

_start:
    li a0, 42       # Load immediate 42 into register a0
    li a1, 10       # Load immediate 10 into register a1
    add a2, a0, a1  # a2 = a0 + a1 (42 + 10)
    ecall           # Exit
