#include <branch/context/header/context.hpp>
#include <tuple>
#include <any>

    static thread_local branch::context::context_entity* current_context;
namespace branch     {
    enum  state_code { standby, running, finished };

    template <typename T>
    class branch { };
    
    template <typename R, typename... Args>
    class branch<R(Args...)> : public context::execution_wrapper
    {
    public:
        branch(R(*branch_exec)(Args...), Args... branch_args)
            : branch_executor(branch_exec)                    ,
              branch_state   (state_code::standby)            ,
              branch_argument(std::make_tuple(branch_args...)),
              branch_caller  (current_context)                { }

        void operator() (context::context_entity& next)
        {
            context::context_entity* prev = current_context;
            current_context               = &next          ;

            if(branch_state == state_code::standby) {
                branch_state = state_code::running;
                context::execute_to(*this, next);
            }
            else
                context::switch_to (*this, next);
        }

    protected:
        R                 (*branch_executor)(Args...);
        std::tuple<Args...> branch_argument          ;

    protected:
        state_code               branch_state ;
        void                     execute()    { std::apply(branch_executor, branch_argument); }
    };
}