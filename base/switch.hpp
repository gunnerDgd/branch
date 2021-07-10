#include <branch/context/header/execution_context.hpp>
#include <branch/context/header/execution_stack.hpp>
#include <branch/context/header/trace_context.hpp>

namespace branch  {
namespace context {

    void BRANCH_PRESERVE save           (branch::context::context_entity&);
    void                 switch_to      (branch::context::context_entity&, branch::context::context_entity&);
    void                 switch_context (branch::context::context_entity&); // Save and Switch.

}
}

void BRANCH_PRESERVE branch::context::save(branch::context::context_entity& ctx_ent)
{
    branch::context::store_context(ctx_ent.context_exec_ctx);
    branch::context::store_stack  (ctx_ent.context_exec_stk);
    
    branch::context::trace_base_pointer       (ctx_ent.context_exec_prev);
    branch::context::trace_stack_pointer      (ctx_ent.context_exec_prev);
    branch::context::trace_instruction_pointer(ctx_ent.context_exec_prev);
}

void branch::context::switch_to (branch::context::context_entity& curr, branch::context::context_entity& next)
{
    branch::context::save          (curr);
    branch::context::switch_context(next);
}

void branch::context::switch_context(branch::context::context_entity& next)
{
    branch::context::load_stack_context(next.context_exec_stk);
    branch::context::
}