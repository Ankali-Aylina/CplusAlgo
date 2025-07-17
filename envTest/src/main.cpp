#include <iostream>
#include <vector>
#include "sorting.h" // 项目头文件

int main()
{
    // C++11 特性测试
    std::vector<int> nums = {5, 2, 9, 1, 5, 6}; // 初始化列表
    auto print = [](const int &n)
    { std::cout << n << " "; }; // Lambda表达式

    std::cout << "Original: ";
    for (int n : nums)
    { // 范围for循环
        print(n);
    }

    quick_sort(nums);

    std::cout << "\nSorted: ";
    for (int n : nums)
    {
        print(n);
    }

    std::cout << "\nC++11 on Windows works!" << std::endl;
    return 0;
}
