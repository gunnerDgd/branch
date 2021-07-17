%include "execution_context.asm"
%include "execution_stack.asm"

; void context_current(branch::context::context_entity&)
global context_current:function

; void context_switch (branch::context::context_entity& prev, branch::context::context_entity& next)
; prev : rdi, next : rsi
global context_switch:function

section .data
    context_entity_pointer:      dq 0x00

section .text
context_current:
    ; Current
    ; RDI : branch::context::context_entity
    call store_cpu_context   ; RDI Has Entity Object.

    add  rdi, 0x40
    call store_stack_context ; RDI Has Stack Entity Object.

    sub  rdi, 0x40           ; Restore RDI Value.
    ret

context_switch:
; Current State
; RDI : prev, RSI : next
    call current_context                                ; RDI : Previous Context Entity
    mov  rdi, rsi                                       ; Previous Context Entity is Useless.
    
    mov  context_entity_pointer, rdi                    ; Back up RDI Register (Pointer of the Next Context Entity)
    call load_cpu_context                               ; RDI : Next Context Entity (Prev Context Entity Deleted.)
    
    xchg context_entity_pointer, rdi                    ; Back up Next Context's RDI Register.
    add  rdi                   , 0x40
    
    call context_load_stack
    xchg context_entity_pointer, rdi

    jmp  context_entity_pointer