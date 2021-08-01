#include <branch/branch.hpp>

void test_1();
void test_2();

branch::branch<void()> br_test_1(test_1), br_test_2(test_2);
branch::branch<int()>  br_main;

int main()
{
    br_main(br_test_1);
}

void test_1()
{
    std::cout << "test_1 #1\n";
    br_test_1(br_test_2);
    std::cout << "test_2 #2\n";
    br_test_1(br_test_2);
}

void test_2()
{
    std::cout << "test_2 #1\n";
    br_test_2(br_test_1);
    std::cout << "test_2 #2\n";
    br_test_2(br_main);
}