#include <branch/context/header/context.hpp>

namespace coroutine {

    class co_exec_wrapper     : public  { public: virtual void execute() = 0; }

    template <typename T>
    class co_exec { };
    
    template <typename T, typename... Args>
    class co_exec<T(Args...)> : public co_exec_wrapper
    {
    public:
        co_exec()
        void execute() override                 { std::apply(co_exec_fp, co_exec_args); }

        T                 (*co_exec_fp)(Args...);
        std::tuple<Args...> co_exec_args        ;
    }

    class coroutine
    {
    public:
        template <typename R, typename... Args>
        coroutine(R(*exec)(Args...), Args... args)
        {
            co_child = new co_exec<R(Args...)>;
        }

    private:
        std::tuple<Args...> co_args          ;
        R                 (*co_exec)(Args...);
        co_exec_wrapper*    co_child         ;
    }

}