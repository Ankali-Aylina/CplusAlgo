#include "main.h"
#include <vector>

int main()
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
            else
            {
                long long new_rabbits = rabbits[month - 1] + rabbits[month - 2]; // 第三个月开始每个月兔子数为前两个月之和。
                rabbits.push_back(new_rabbits);
            }
            std::cout << "Month " << month + 1 << ": " << rabbits[month] << " rabbits" << std::endl;
        }

        return 0;
    }
}
