; Built in NASM Environment.
; Store / Load Stack Context (RBP, RSP Register) of the Function Frame.

global context_store_stack:function
global context_load_stack:function

section .text

; void context_store_stack(branch::context::execution_stack&)
context_store_stack:
    push rax
    
    mov  rax              , qword[rbp]
    mov  qword[rdi]       , rax

    add  rax              , 0x10
    mov  qword[rdi + 0x08], rax

    pop  rax
    ret

; void context_load_stack(branch::context::execution_stack&)
; Uses RDI Register to Save Return Address.

context_load_stack:
    mov  rax, qword[rsp]
    
    mov  rbp, qword[rdi]
    mov  rsp, qword[rdi + 0x08]

    jmp  rax