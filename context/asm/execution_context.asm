; Built in NASM Environment.
; Store / Load CPU Context (Register) of the Function Frame.

global store_cpu_context:function
global load_cpu_context:function

section .text

; void store_cpu_context(branch::context::execution_context&)
; By System V Function Convention, RDI Register will be used to store parameter.

store_cpu_context:
    sub rsp, 0x10                           ; 16 - Byte Alignment.
                                            ; Stores Generic Purposed Register.

    mov qword[rdi]       , rax
    mov qword[rdi + 0x08], rbx
    mov qword[rdi + 0x10], rcx
    mov qword[rdi + 0x18], rdx
                                            ; Stores Stack Instruction Register.
    mov qword[rdi + 0x20], rsi
    mov qword[rdi + 0x28], rdi

    mov [rsp]            , rax
    mov rax              , qword[rbp + 0x08]

    mov qword[rdi + 0x30], rax
    mov rax              , [rsp]

    add rsp, 0x10                           ; Deallocate Temporal Memory.
    ret


; void load_cpu_context(branch::context::execution_context&)
; By System V Function Convention, RDI Register will be used to store parameter.

load_cpu_context:
; Loads Generic Purposed Register.

    mov rax, qword[rdi]
    mov rbx, qword[rdi + 0x08]
    mov rcx, qword[rdi + 0x10]
    mov rdx, qword[rdi + 0x18]

    mov rsi, qword[rdi + 0x20]
    mov r10, qword[rdi + 0x28]
    mov rdi, r10

    ret

