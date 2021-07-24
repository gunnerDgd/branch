#include <branch/branch_types.hpp>

namespace branch {

    template <typename T, typename R, typename... Args>
    branch<R> start(R(*)(Args...), Args...);
}

template <typename T, typename R, typename... Args>
branch::branch<T> branch::start(R(*branch_exec)(Args...), Args... branch_args)
{
    (context::execution_wrapper*)&next->exec_parent = prev ;
    current_context                                 = &next;

    context_store_cpu();
}