#include <branch/branch.hpp>

void test_1(std::string a);
void test_2(std::string b);

branch::branch<void(std::string)> br_test_1(test_1, std::string("Hello Test 1")), br_test_2(test_2, std::string("Hello Test 2"));
branch::branch<>                  br_main;

int main()
{
    br_main(br_test_1);
    std::cout << "Finished !!~\n";
}

void test_1(std::string a)
{
    std::cout << "test_1 #1" << a << "\n";
    br_test_1(br_test_2);
    std::cout << "test_2 #2" << a << "\n";
    br_test_1(br_test_2);
}

void test_2(std::string b)
{
    std::cout << "test_2 #1" << b << "\n";
    br_test_2(br_test_1);
    std::cout << "test_2 #2" << b << "\n";
    br_test_2(br_main);
}