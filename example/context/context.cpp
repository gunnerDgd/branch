#include <branch/context/header/context.hpp>

int main()
{
    branch::context::context_entity test_ctx ;
    branch::context::current       (test_ctx);

    asm volatile ("movq $0x08, %rdx");
    std::cout << test_ctx.context.rdx << std::endl;
}