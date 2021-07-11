#pragma once
#include <iostream>

#define BRANCH_PRESERVE __attribute__((always_inline))

namespace branch  {
namespace context {

    class alignas(16) execution_context // 64 Byte.
    {
    public:
        union
        {
            struct
            {
                uint64_t rax, rbx, rcx, rdx,
                         rsi, rdi, rip     ;
            };

            uint64_t     register_block [7];
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