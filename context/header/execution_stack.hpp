#include <branch/context/header/types.hpp>

extern "C"
{
    void store_stack_context(branch::context::execution_stack&);
    void load_stack_context (branch::context::execution_stack&);
}

namespace branch  {
namespace context {

    void __attribute__((always_inline)) store_stack(branch::context::execution_stack& exec_stk) { store_stack_context(exec_stk); }
    void __attribute__((always_inline)) load_stack (branch::context::execution_stack& exec_stk) { load_stack_context (exec_stk); }

}
}