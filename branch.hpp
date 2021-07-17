#include <branch/context/header/context.hpp>
#include <functional>
#include <tuple>

namespace branch {

    template <typename T>
    class branch { };

    template <typename R>
    class branch<R(void)>    : public context::context_entity
    {
    public:
        branch    (R(*br_exec)(void));
        void start(context::context_entity& br_prev)     { context::switch_to(br_prev, branch_executor); }

    protected:
        R    (*branch_executor)(void);
    };

    template <typename R, typename... Args>
    class branch<R(Args...)> : public context::context_entity
    {
    public:
        branch    (R(*br_exec)(Args...), Args... br_args);
        void start(context::context_entity& br_prev)     { context::switch_to(br_prev, branch_executor, std::forward<Args...>(branch_argument)); }

    protected:
        std::tuple<Args...>       branch_argument          ;
        R                       (*branch_executor)(Args...);
    };
}

template <typename R, typename... Args>
branch::branch<R(Args...)>::branch(R(*br_exec)(Args...), Args... br_args)
    : branch_argument(std::make_tuple(br_args...)),
      branch_executor(br_exec)                    {}

template <typename R>
branch::branch<R(void)>::branch(R(*br_exec)(void))
    : branch_executor(br_exec)                   {}