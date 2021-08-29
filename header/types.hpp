#pragma once
#include <iostream>
#include <tuple>

#define BRANCH_PRESERVE __attribute__((always_inline))

namespace branch  {
namespace context {
    
    class alignas(16) cpu_register // 64 Byte.
    {
    public:
        union
        {
            struct
            {
                uint64_t     rax, rbx, rcx, rdx,
                             rsi, rdi, rip     ; // 56 Byte
            };  uint64_t     register_block[7] ;
        };
    };

    class alignas(16) frame // 16 Byte
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
        cpu_register cpu_context  ; // 64
        frame        stack_context; // 16
    };

    enum  execution_state
    {
        standby,
        running,
        stopped
    };

    template <typename Fp, typename... Args>
    struct execution_argument
    {
        execution_argument(Fp f, Args... a)
            : exec_argument(std::forward_as_tuple(a...)),
              exec_function(f)                          { std::cout << &std::get<1>(exec_argument) << std::endl; }

        Fp                  exec_function;
        std::tuple<Args...> exec_argument;
    };

    /*class execution_wrapper : public context_entity 
    {
    public:
        execution_state get_state () { return executor_state; }
        virtual void    execute   ()                   = 0;

    protected:
        execution_state executor_state;
    };*/

    /*
    Execution Wrapper Object Will be Obsolete...
    */
}
}