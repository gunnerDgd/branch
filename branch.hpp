#include <branch/context/header/context.hpp>
#include <functional>
#include <tuple>

namespace branch {

    enum  state
    {
        standby,
        running,
        ended
    };

    template <typename R, typename... Args>
    class branch : public context_entity
    {
    public:
        branch    (std::function<R(Args...)> br_exec, Args... br_args);
        void start()
        {
            if (branch_state == branch::state::standby)
                std::apply(branch_executor, branch_argument);
        }

    protected:
        std::tuple<Args...>       branch_argument     ;
        std::function<R(Args...)> branch_executor     ;
        branch::state             branch_state        ; 
    };
}

template <typename R, typename... Args>
branch::branch::branch(std::function<R(Args...)> br_exec, Args... br_args)
    : branch_argument(std::make_tuple(br_args...)),
      branch_executor(branch_executor)            ,
      branch_state   (branch::state::standby)     { }