#include <branch/context/header/context.hpp>
#include <memory/vmem/vmem.hpp>
#include <tuple>

namespace branch {

    template <typename T = void>
    class branch { };
    
    template <>
    class branch<void> : public context::execution_wrapper // Capture Current Branch (Context)
    {
    public:
        branch         ()                            { executor_state = context::execution_state::running; }
        void operator()(execution_wrapper&)          ;
    protected:
        void execute   ()                   override { }
    };

    template <typename R, typename... Args>
    class branch<R(Args...)> : public context::execution_wrapper, private memory::vmem
    {
    public:
        branch(R(*br_exec)(Args...), Args... br_args);
        void operator()(execution_wrapper&)          ;

    protected:
        std::tuple<Args...> branch_argument                 ;
        R                 (*branch_executor)(Args...)       ;
    protected:
        void execute   ()                   override;
    };
}

template <typename R, typename... Args>
branch::branch<R(Args...)>::branch(R(*br_exec)(Args...), Args... br_args)
    : vmem              (::memory::protect_type::read  | 
                         ::memory::protect_type::write | 
                         ::memory::protect_type::execute),
      branch_argument   (std::make_tuple(br_args...))    ,
      branch_executor   (br_exec)                    
{
    stack_context.rsp = reinterpret_cast<uint64_t>(memory_address) + memory_block_size;
    stack_context.rbp = stack_context.rbp;
}

template <typename R, typename... Args>
void branch::branch<R(Args...)>::execute()
{
    if(executor_state != context::execution_state::standby) return;

    executor_state     = context::execution_state::running;
    std::apply          (branch_executor, branch_argument);
}

template <typename R, typename... Args>
void branch::branch<R(Args...)>::operator()(context::execution_wrapper& exec)
{
    if      (exec.get_state() == context::execution_state::standby)
        context::execute_to(*this, exec);
    else if (exec.get_state() == context::execution_state::running)
        context::switch_to (*this, exec);
    else
        return;
}

void branch::branch<void>::operator()(execution_wrapper& exec)
{
    if      (exec.get_state() == context::execution_state::standby)
        context::execute_to(*this, exec);
    else if (exec.get_state() == context::execution_state::running)
        context::switch_to (*this, exec);
    else
        return;
}