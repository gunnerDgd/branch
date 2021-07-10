#pragma once
#include <iostream>

namespace branch  {
namespace context {

    class alignas(16) execution_context
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

    class alignas(16) execution_stack
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp; };
            uint64_t    stack_register[2];
        };
    };

    class alignas(16) trace
    {
    public:
        union
        {
            struct { uint64_t rbp, rsp, rip; };
            uint64_t          caller_block[3];
        };
    };

}
}