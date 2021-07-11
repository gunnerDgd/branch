#include <branch/context/header/context.hpp>

int main()
{
    branch::context::context_entity test_ctx;
    std::cout << &test_ctx << std::endl;
    std::cout << &test_ctx.context_exec_ctx  << std::endl;
    std::cout << &test_ctx.context_exec_stk  << std::endl;
    std::cout << &test_ctx.context_exec_prev << std::endl;
}