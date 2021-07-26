#include <branch/branch.hpp>

void branch_test_1();
void branch_test_2();

branch::branch<void()> branch_1(branch_test_1), branch_2(branch_test_2);

int main()
{
    branch::branch<int()> main_branch(main);
    branch::context::execute_to(main_branch, branch_1);
    std::cout << "Main Branch\n";
}

void branch_test_1()
{
    std::cout << "Branch Test #1\n";
    branch::context::execute_to(branch_1, branch_2);
    std::cout << "Branch Test #1(2)\n";
    branch::context::switch_to (branch_1, branch_2);
}

void branch_test_2()
{
    std::cout << "Branch Test #2\n";
    branch::context::switch_to(branch_2, branch_1);
    std::cout << "Branch Test #2(2)\n";
}