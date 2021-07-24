; void context_switch_to       (branch::context::context_entity& next)
global context_switch:function


section .text
context_switch_to:
    mov rax, qword[rdi + 0x30]

    add rdi, 0x40
    mov rbp, qword[rdi]
    
    mov rsp, qword[rdi + 0x08]
    jmp rax