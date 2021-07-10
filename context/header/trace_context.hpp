#include <branch/context/header/types.hpp>

extern "C"
{
    void trace_caller_rbp(branch::context::trace& ctx_tr);
    void trace_caller_rip(branch::context::trace& ctx_tr);
    void trace_caller_rsp(branch::context::trace& ctx_tr);
}

namespace branch  {
namespace context {

    void __attribute__((always_inline)) trace_base_pointer       (branch::context::trace& ctx_tr) { trace_caller_rbp(ctx_tr); }
    void __attribute__((always_inline)) trace_stack_pointer      (branch::context::trace& ctx_tr) { trace_caller_rsp(ctx_tr); }
    void __attribute__((always_inline)) trace_instruction_pointer(branch::context::trace& ctx_tr) { trace_caller_rip(ctx_tr); }

}
}

