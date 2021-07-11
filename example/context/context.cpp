#include <branch/context/header/context.hpp>

void tracer()
{
    branch::context::context_entity ctx ;
    current_context(ctx);

    std::cout << ctx.context.rip << std::endl;
}

int main()
{
    std::cout << (uint64_t)main << std::endl;
    tracer();

    std::cout << "Hello World\n";
}