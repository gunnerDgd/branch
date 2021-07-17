#include <branch/coroutine/coroutine.hpp>
#include <string>

 branch::coroutine::enumerator co_enum;

void test_1()
{
    branch::branch<void()> co_tst1(test_1);
    std::cout           << "Test 1 #1\n"  ;

    co_enum.yield(std::string("Hello Coroutine! (test_1)\n"));
    
    auto co_yield = co_enum.advance<std::string>(co_tst1);
    std::cout           << co_yield;
    
    co_enum.yield(std::string("Hello Coroutine! (test_1 (2))\n"));
}

int main()
{
    branch::branch<void()> co_tst1(test_1);
    auto co_yield        = co_enum.advance<std::string>(co_tst1);
    std::cout << co_yield;
    co_yield             = co_enum.advance<std::string>(co_tst1);

    std::cout << co_yield;
}