#include <branch/context/header/types.hpp>

extern "C"
{
    void store_cpu_context(branch::context::execution_context& exec_ctx);
    void load_cpu_context (branch::context::execution_context& exec_ctx);
}

namespace branch  {
namespace context {

    void __attribute__((always_inline)) store_context(branch::context::execution_context& exec_ctx) { store_cpu_context(exec_ctx); }
    void __attribute__((always_inline)) load_context (branch::context::execution_context& exec_ctx) { load_cpu_context (exec_ctx); }
}
}