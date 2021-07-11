#include <branch/context/header/types.hpp>
#include <tuple>

extern "C"
{
    void switch_context (branch::context::context_entity&, branch::context::context_entity&);
    void current_context(branch::context::context_entity&);
}

namespace branch  {
namespace context {

    template <typename R, typename... Args>
    void switch_to(branch::context::context_entity& prev, R(*next)(Args...), Args... next_args);
    void switch_to(branch::context::context_entity& prev, branch::context::context_entity& next) { switch_context (prev, next); }
    void current  (branch::context::context_entity& curr)                                        { current_context(curr);       }

}
}

template <typename R, typename... Args>
void branch::context::switch_to(branch::context::context_entity& prev, R(*next)(Args...), Args... next_args)
{
    current_context(prev);
    std::apply     (next, std::make_tuple(next_args...));
}