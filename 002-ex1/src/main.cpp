#include "main.h"
#include <vector>

double exF(int num)
{
    if (num < 1 || num > 30)
    {
        std::cout << "输入错误！" << std::endl;
        return -1;
    }
    std::vector<double> fib;
    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            fib.push_back(1.0)
        }
    }
}
int main()
{
    std::cout << "请输入一个整数：(1<=n<=30)" << std::endl;
    int n;
    std::cin >> n;
    std::cout << " 结果为：" << exF(n) << std::endl;
    return 0;
}
