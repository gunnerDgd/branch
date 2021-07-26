#include <branch/scheduler/scheduler.hpp>
#include <tuple>

namespace branch {

    template <typename T>
    class branch { };
    
    template <typename R, typename... Args>
    class branch<R(Args...)> : public context::execution_wrapper
    {
    public:
        branch(R(*br_exec)(Args...), Args... br_args);
        branch(R(*br_exec)(Args...), Args... br_args, scheduler& br_sched);

    protected:
        std::tuple<Args...> branch_argument                 ;
        R                 (*branch_executor)(Args...)       ;
        scheduler          *branch_scheduler       = nullptr;

    private:
        void execute      () override             { std::apply(branch_executor, branch_argument); }
    };
}

template <typename R, typename... Args>
branch::branch<R(Args...)>::branch(R(*br_exec)(Args...), Args... br_args)
    : branch_argument (std::make_tuple(br_args...)),
      branch_executor (br_exec)                    {  }

template <typename R, typename... Args>
branch::branch<R(Args...)>::branch(R(*br_exec)(Args...), Args... br_args, scheduler& br_sched)
    : branch_argument (std::make_tuple(br_args...)),
      branch_executor (br_exec)                    ,
      branch_scheduler(&br_sched)                  {  }