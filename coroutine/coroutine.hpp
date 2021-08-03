#include <branch/context/header/context.hpp>
#include <any>

namespace branch {
    class coroutine : public branch<>
    {
    public:
        template <typename R, typename... Args>
        coroutine(R(*)(Args...), Args...);

    protected:
        execution_wrapper* co_friend;
    };
}

template <typename R, typename... Args>
branch::coroutine::coroutine(R(*co_exec)(Args...), Args... co_args)
{
    co_friend = new branch::branch<R(Args...)>();
}