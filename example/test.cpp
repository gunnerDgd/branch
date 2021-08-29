#include <branch/branch.hpp>

void test(branch::branch<>& current_branch, branch::branch<>& main_branch)
{
    std::cout << "Hello World\n";
    current_branch(main_branch);
    std::cout << "Hello World 2\n";
    current_branch(main_branch);
}

int main()
{
    branch::branch<> main_branch, test_branch(main_branch, test, main_branch);
    
    std::cout << "Hello World!!\n";
    main_branch(test_branch);
    std::cout << "Hello World!! 2\n";
} 