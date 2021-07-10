#include <branch/context/header/types.hpp>

extern "C"
{
    void store_cpu_context(branch::context::execution_context& exec_ctx);
    void load_cpu_context (branch::context::execution_context& exec_ctx);
}

namespace branch  {
namespace context {

    void BRANCH_PRESERVE store_context(branch::context::execution_context& exec_ctx) { store_cpu_context(exec_ctx); }
    void BRANCH_PRESERVE load_context (branch::context::execution_context& exec_ctx) { load_cpu_context (exec_ctx); }
}
}