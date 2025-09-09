#include "main.h"

int selectFun()
{
    int x;
    cout << "请选择函数：" << endl;
    cout << "1:等差数列\n2:等比数列\n3:阶乘" << endl;
    cin >> x;
    return x;
}

/// @brief 求解第n项的值
/// @param n 第n项
/// @return 第n项的值
int find(int n)
{
    int res;
    if (n == 1)
    {
        res = 1;
    }
    else
    {
        res = find(n - 1) + 3; // 第n项等于前一项+3
    }

    return res;
}

int geometricRatio(int n)
{
    int res;
    if (n == 1)
    {
        res = 2;
    }
    else
    {
        res = geometricRatio(n - 1) * 2;
    }
    return res;
}

int factorial(int n)
{
    int res;
    if (n == 1)
    {
        res = 1;
    }
    else
    {
        res = factorial(n - 1) * n;
    }

    return res;
}

int main()
{
    int x, y;

    x = selectFun();
    switch (x)
    {
    case 1:
        cout << "等差数列：1 4 7 10……" << endl
             << "请输入所需求解的项：" << endl;
        cin >> y;
        cout << "第" << y << "项的值为:" << find(y) << endl;
        break;
    case 2:
        cout << "等比数列：2 4 8 16……" << endl
             << "请输入所需求解的项：" << endl;
        cin >> y;
        cout << "第" << y << "项的值为:" << geometricRatio(y) << endl;
        break;
    case 3:
        cout << "阶乘：" << endl
             << "请输入所需求解的阶乘：" << endl;
        cin >> y;
        cout << y << "的阶乘为:" << factorial(y) << endl;
        break;
    default:
        break;
    }

    return 0;
}
