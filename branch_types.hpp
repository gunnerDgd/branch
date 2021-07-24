#include <branch/context/header/types.hpp>
#include <functional>
#include <tuple>

namespace branch {
    static thread_local context::context_entity* current_context;

    template <typename R>
    class branch : public context::context_entity
    {
    public:
        template <typename Fn, typename... Args>
        branch(Fn& branch_exec, Args... branch_argument)
            : branch_parent(current_context)
        {
            current_context = this;   
            std::apply       (branch_exec, std::make_tuple(branch_argument...));
        }

        template <typename U>
        branch(branch<U>& branch_convert)
            : branch_parent(branch_convert.branch_parent)
        {
            
        }

    private:
        context::context_entity* branch_parent      ;
        R                        branch_return_value;
    };
}
