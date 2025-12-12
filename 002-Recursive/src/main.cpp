#include "main.h"
#include <vector>

void fibonacci()
{
    std::vector<long long> rabbits;
    for (int month = 0; month < 50; ++month)
    {
        if (month == 0)
        {
            rabbits.push_back(2); // 开始的两只兔子
        }
        else if (month == 1)
        {
            rabbits.push_back(2); // 第二个月也只有2只兔子
        }
        else
        {
            long long new_rabbits = rabbits[month - 1] + rabbits[month - 2]; // 第三个月开始每个月兔子数为前两个月之和。
            rabbits.push_back(new_rabbits);
        }
        std::cout << "Month " << month + 1 << ": " << rabbits[month] << " rabbits" << std::endl;
    }
}

void Block()
{
    std::vector<int> blocks;
    for (int n = 1; n < 100; ++n)
    {
        if (n == 1)
        {
            blocks.push_back(1);
        }
        else
        {
            int new_blocks = blocks[n - 2] + n; // 存储总数的下标与当前计算层数相差2
            blocks.push_back(new_blocks);
        }
        std::cout << "第" << n << "层总计有：" << blocks[n - 1] << " 个方块" << std::endl; // 存储总数的下标与当前层数相差1
    }
}
int main()
{
    fibonacci();
    std::cout << "-------------------" << std::endl;
    Block();
    return 0;
}
