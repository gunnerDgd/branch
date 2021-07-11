#include <branch/context/header/context.hpp>

int main()
{
    branch::context::context_entity test_ctx;
    std::cout << &test_ctx             << std::endl;
    std::cout << &test_ctx.context     << std::endl;
    std::cout << &test_ctx.context.rax << std::endl;
    std::cout << &test_ctx.context.rbx << std::endl;
}