%include "execution_context.asm"
%include "execution_stack.asm"

; void current_context(branch::context::context_entity&)
global current_context:function

; void switch_context(branch::context::context_entity& prev, branch::context::context_entity& next)
; prev : rdi, next : rsi
global switch_context:function

section .text
current_context:
    ; Current
    ; RDI : branch::context::context_entity
    call store_cpu_context   ; RDI Has Entity Object.

    add  rdi, 0x40
    call store_stack_context ; RDI Has Stack Entity Object.

    ret

switch_context:
    mov  r8, rdi          ; Previous Context Entity
    mov  r9, rsi          ; Next Context Entity
    call current_context  ; RDI : Previous Context Entity
    
    lea  rdi, [rsi]       ; RSI : Next Context Entity
    call load_cpu_context ; RDI : Next Context Entity (Prev Context Entity Deleted.)
    
    mov  rdi, r8          ; R8  : Next Context's RDI Register Context.
    lea  rdi, [r9 + 0x40] ; RDI : Next Context's Stack Frame
    call load_stack_context

    mov  rdi, r8                      ; RDI Restore
    mov  r8 , qword[r9 + 0x50 + 0x20] ; Get RIP Address

    call r8
    