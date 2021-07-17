#pragma once
#include <iostream>

#define BRANCH_PRESERVE __attribute__((always_inline))

namespace branch  {
namespace context {

    class alignas(32) simd_context     { public: uint64_t simd_register[4]; }; // 32 Byte
    class alignas(16) execution_context // 64 Byte.
    {
    public:
        union
        {
            struct
            {
                uint64_t     rax, rbx, rcx, rdx,
                             rsi, rdi, rip     ; // 56 Byte
                simd_context register_simd [16]; // 32 Byte * 16 = 512 Byte
            };  uint64_t     register_block[72]; // Size : 72 * 8 = 576 Byte
        };
    };

    class alignas(16) execution_stack // 16 Byte
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp; }      ;
            uint64_t          stack_register[2];
        };
    };

    struct context_entity
    {
        execution_context context; // 64
        execution_stack   stack  ; // 16
    };

}
}