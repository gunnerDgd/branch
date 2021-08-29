#include <branch/coroutine.hpp>

void test(coroutine::coroutine<>& main)
{
    std::cout << "Test\n";
    main(3);
    std::cout << "Test 2\n";
}

int main()
{
    std::cout << "Main\n";
    coroutine::coroutine<> main(test);
    std::cout << main.get_yield_value<int>() << std::endl;
}