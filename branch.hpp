#include <branch/context/execution_context.hpp>
#include <branch/context/execution_stack.hpp>
#include <branch/context/trace_context.hpp>

#include <functional>
#include <future>

namespace branch {

    template <typename R>
    class branch<R(void)>
    {
    public:
        branch                     (std::function<R(void)> br_func);
        std::promise<R> operator() ();

    private:
        std::function<R(void)> branch_execution;
        std::promise<R>        branch
    };


    template <typename R, typename... Args>
    class branch<R(Args...)>
    {
    public:
        branch                     (std::function<R(Args...)> br_func,
                                    Args...                   br_args);

        std::promise<R> operator() ();

    private:
        std::function<R(Args...)> branch_execution;
        std::tuple<Args...>       branch_argument ;
    };

}

template <typename R>
branch::branch::branch(std::function<R(void)> br_func)
    : branch_execution(br_func) { }

template <typename R>
std::promise<R> branch::branch::operator() ()
{
    std::promise<R> branch_return_value;

}