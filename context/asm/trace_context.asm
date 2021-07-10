global trace_caller_rbp:function
global trace_caller_rsp:function
global trace_caller_rip:function

global current_rbp:function
global current_rsp:function

section .text

trace_caller_rbp:
    push rax
    mov  rax       , qword[rbp]
    mov  qword[rdi], rax

    pop  rax
    retq

trace_caller_rsp:
    push rax
    mov  rax, rbp

    add  rax              , 0x10
    mov  qword[rdi + 0x08], rax

    pop  rax
    retq

trace_caller_rip:
    push rax
    mov  rax              , qword[rbp + 0x08]
    mov  qword[rdi + 0x10], rax

    pop  rax
    retq