section .data
    arquivo db "LeitorArquivosSysCall/texto.txt", 0

section .bss
    buff resb 1024
    ru resd 1
    bytes resd 1

section .text
    global main

main:
    ; open(arquivo, O_RDONLY)
    mov rax, 2
    mov rdi, arquivo
    mov rsi, 0
    syscall
    mov [ru], eax
    
    ; read(ru, buff, 1024)
    mov edi, [ru]
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
    ; close(ru)
    mov edi, [ru]
    mov rax, 3
    syscall
    
    xor eax, eax
    ret