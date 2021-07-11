#include <branch/context/header/context.hpp>

branch::context::context_entity main_branch, branch_1, branch_2;

void branch_test_1();
void branch_test_2();
void branch_launch()
{
    branch::context::switch_to(main_branch, branch_test_1);
}

int main()
{
    branch_launch();
    std::cout << "Main Branch\n";
}

void branch_test_1()
{
    std::cout << "Branch Test #1\n";
    branch::context::switch_to(branch_1, branch_test_2);
    std::cout << "Branch Test #1(2)\n";
    branch::context::switch_to(branch_1, main_branch);
}

void branch_test_2()
{
    std::cout << "Branch Test #2\n";
    branch::context::switch_to(branch_2, branch_1);
}