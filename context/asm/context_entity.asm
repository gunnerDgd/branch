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

    sub  rdi, 0x40           ; Restore RDI Value.
    ret

switch_context:
; Current State
; RDI : prev, RSI : next
    call current_context  ; RDI : Previous Context Entity
    mov  rdi, rsi         ; Previous Context Entity is Useless.
    
    mov  r10, rdi         ; Back up RDI Register (Pointer of the Next Context Entity)
    call load_cpu_context ; RDI : Next Context Entity (Prev Context Entity Deleted.)
    
    mov  r11, rdi         ; Back up Next Context's RDI Register.
    mov  rdi, r10         ; R10  : Next Context's RDI Register Pointer.
    
                          ; R10 : Pointer Of the Next Context Entity.
                          ; R11 : Next Context's RDI Register
                          ; R12 : Next Context's RIP Register

    add  rdi, 0x40
    call load_stack_context
    
    mov  r12, qword[rdi + 0x30]
    mov  rdi, r11

    jmp  r12