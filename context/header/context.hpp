#include <branch/branch.hpp>
#include <tuple>

extern "C"
{
    void context_store_cpu    (branch::context::cpu_register& curr);
    void context_load_cpu     (branch::context::cpu_register& curr);

    void context_capture_stack(branch::context::frame& curr);
    void context_store_stack  (branch::context::frame& curr);
    void context_load_stack   (branch::context::frame& curr);

    void context_switch_to    (branch::context::context_entity& next);
}

namespace branch   {
namespace context  {

namespace internal {
    void switch_to (branch::context::context_entity& prev, branch::context::context_entity& next);
    template <typename R, typename... Args>
    void execute_to(branch::context::context_entity& prev, branch::branch<R(Args...)>     & next);
}

    void switch_to (branch::context::context_entity& prev, branch::context::context_entity& next);
    template <typename R, typename... Args>
    void execute_to(branch::context::context_entity& prev, branch::branch<R(Args...)>     & next);
}
}

template <typename R, typename... Args>
void branch::context::internal::execute_to(branch::context::context_entity& prev, branch::branch<R(Args...)>& next)
{
    context_store_cpu (prev);
    context_load_stack(next);
    branch::branch<R(Args...)>::launch(next);
}

template <typename R, typename... Args>
void branch::context          ::execute_to(branch::context::context_entity& prev, branch::branch<R(Args...)>& next)
{
    volatile context_entity* instack_prev = &prev;
    volatile context_entity* instack_next = &next;
    
    internal::execute_to(prev, next);
    context_load_cpu    (*prev)     ;
}

void branch::context::internal::switch_to(branch::context::context_entity& prev, branch::context::context_entity& next)
{
    context_store_cpu  (prev); // Store Previous CPU Context.
    context_store_stack(prev);
    
    context_switch_to  (next);
}

void branch::context          ::switch_to(branch::context::context_entity& prev, branch::context::context_entity& next)
{
    volatile context_entity* instack_prev = &prev;
    volatile context_entity* instack_next = &next;
    
    internal::switch_to(prev, next);
    context_load_cpu   (*prev)     ;
    
}