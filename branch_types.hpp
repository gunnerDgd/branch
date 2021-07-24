#include <branch/context/header/types.hpp>
#include <tuple>
#include <any>

namespace branch     {
    enum  state_code { standby, running, finished };
    
    template <typename R, typename... Args>
    class branch : public context::context_entity
    {
    public:
        using  executor_t      = R(*)(branch<R(Args...)>, Args...)      ;
        using  executor_args_t = std::tuple<branch<R(Args...)>, Args...>;
    public:
        branch(executor_t branch_exec, Args... branch_args)
            : branch_executor(branch_exec)                          ,
              branch_state   (state_code::standby)                  ,
              branch_args    (std::make_tuple(*this, branch_args...)) { }

        friend void launch    (branch<R(Args...)>& next)   { std::apply(branch_executor, branch_argument); }
        template <typename Tr, typename... Targs>
        void        operator()(branch<Tr(Targs...)>& prev) { context::execute_to(prev, *this); }

    protected:
        executor_t      branch_executor;
        executor_args_t branch_argument;
        state_code      branch_state   ;
    };
}