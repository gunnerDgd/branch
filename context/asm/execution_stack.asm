; Built in NASM Environment.
; Store / Load Stack Context (RBP, RSP Register) of the Function Frame.

global store_stack_context:function
global load_stack_context:function
global trace_caller_stack:function

section .text

; void store_stack_context(branch::context::execution_stack&)

store_stack_context:
    push rax
    
    mov  rax       , qword[rbp]
    mov  qword[rdi], rax

    add  rax              , 0x10
    mov  qword[rdi + 0x08], rax

    pop  rax
    ret

; void load_stack_context(branch::context::execution_stack&)


load_stack_context:
    mov rbp, qword[rdi]
    mov rsp, qword[rdi + 0x08]

    ret