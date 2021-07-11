; Built in NASM Environment.
; Store / Load CPU Context (Register) of the Function Frame.

global store_cpu_context:function
global load_cpu_context:function

section .text


; void store_cpu_context(branch::context::execution_context&)
; By System V Function Convention, RDI Register will be used to store parameter.

store_cpu_context:
    push rax

; Stores Generic Purposed Register.

    mov qword[rdi]       , rax
    mov qword[rdi + 0x08], rbx
    mov qword[rdi + 0x10], rcx
    mov qword[rdi + 0x18], rdx

; Stores Stack Instruction Register.

    mov qword[rdi + 0x20], rsi
    mov qword[rdi + 0x28], rdi
    
    mov rax              , qword[rbp + 0x08]
    mov qword[rdi + 0x30], rax

    pop rax
    ret


; void load_cpu_context(branch::context::execution_context&)
; By System V Function Convention, RDI Register will be used to store parameter.

load_cpu_context:

; Loads Generic Purposed Register.

    sub rsp       , 0x10
    mov qword[rsp], rdi

    mov rax, qword[rdi]
    mov rbx, qword[rdi + 0x08]
    mov rcx, qword[rdi + 0x10]
    mov rdx, qword[rdi + 0x18]

    mov rsi, qword[rdi + 0x20]
    mov rdi, qword[rsp]

    add rsp, 0x10
    ret

