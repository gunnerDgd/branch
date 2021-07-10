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
            struct { uint64_t rbp, rsp; };
            uint64_t    stack_register[2];
        };
    };

    class alignas(16) trace // 32 Byte
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp, rip; };
            uint64_t          caller_block[3];
        };
    };

    struct context_entity
    {
        execution_context context_exec_ctx ; // 64
        execution_stack   context_exec_stk ; // 16
        trace             context_exec_prev; // 32
    };

}
}