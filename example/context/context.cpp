#include <branch/context/header/execution_context.hpp>
#include <branch/context/header/execution_stack.hpp>
#include <branch/context/header/trace_context.hpp>

int main()
{
    std::cout << sizeof(branch::context::trace) << std::endl;
}