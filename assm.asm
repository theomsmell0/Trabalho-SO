section .text
global ler_mostrar

ler_mostrar:
    mov r8, rsi
    mov r9, rdx

    mov rax, 2
    mov rsi, 0
    mov rdx, 0
    syscall

    mov r10, rax

    mov rax, 0
    mov rdi, r10
    mov rsi, r8
    mov rdx, r9
    syscall

    mov rdx, rax
    mov rax, 1
    mov rdi, 1
    mov rsi, r8
    syscall

    mov rax, 3
    mov rdi, r10
    syscall

    ret
