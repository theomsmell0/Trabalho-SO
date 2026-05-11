section .data
    arquivo db "LeitorArquivosSysCall/texto.txt", 0

section .bss
    buff resb 1024
    fd resd 1
    bytes resd 1

section .text
    global _start

_start:
    ; open(arquivo, O_RDONLY)
    mov rax, 2
    mov rdi, arquivo
    mov rsi, 0
    syscall
    mov [fd], eax
    
    ; read(fd, buff, 1024)
    mov edi, [fd]
    mov rsi, buff
    mov rdx, 1024
    mov rax, 0
    syscall
    mov [bytes], eax
    
    ; if (bytes > 0)
    cmp dword [bytes], 0
    jle fim
    
    ; write(1, buff, bytes)
    mov rdi, 1
    mov rsi, buff
    mov rdx, [bytes]
    mov rax, 1
    syscall
    
fim:
    ; close(fd)
    mov edi, [fd]
    mov rax, 3
    syscall
    
    ; exit(0)
    mov rax, 60
    xor rdi, rdi
    syscall