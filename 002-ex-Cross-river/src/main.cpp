#include "main.h"
#include <vector>

void AToB(int x1, int y1)
{
    std::vector<std::vector<int>> data(x1 + 1, std::vector<int>(y1 + 1, 0));
    for (int i = 0; i <= x1; i++)
    {
        for (int j = 0; j <= y1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            if (i == 0 || j == 0)
            {
                data[i][j] = 1;
            }
            else
            {
                data[i][j] = data[i - 1][j] + data[i][j - 1];
            }
        }
    }
    std::cout << "路径条数为：" << data[x1][y1] << std::endl;
}
void HaveHorse(int x1, int y1, int x2, int y2)
{
    std::vector<std::vector<int>> data(x1 + 1, std::vector<int>(y1 + 1, 1));

    data[x2][y2] = 0;
    // if (x2 + 2 <= x1 && y2 - 1 >= 0)
    // {
    //     data[x2 + 2][y2 - 1] = 0;
    // }
    // if (x2 + 2 <= x1 && y2 + 1 <= y1)
    // {
    //     data[x2 + 2][y2 + 1] = 0;
    // }
    // if (x2 + 1 <= x1 && y2 + 2 <= y1)
    // {
    //     data[x2 + 1][y2 + 2] = 0;
    // }
    // if (x2 - 1 >= 0 && y2 + 2 <= y1)
    // {
    //     data[x2 - 1][y2 + 2] = 0;
    // }
    // if (x2 - 2 >= 0 && y2 + 1 <= y1)
    // {
    //     data[x2 - 2][y2 + 1] = 0;
    // }
    // if (x2 - 2 >= 0 && y2 - 1 >= 0)
    // {
    //     data[x2 - 2][y2 - 1] = 0;
    // }
    // if (x2 - 1 >= 0 && y2 - 2 >= 0)
    // {
    //     data[x2 - 1][y2 - 2] = 0;
    // }
    // if (x2 + 1 <= x1 && y2 - 2 >= 0)
    // {
    //     data[x2 + 1][y2 - 2] = 0;
    // }

    /// 优化马的计算

    /// 马的攻击位置
    const int horseMoves[8][2] = {
        {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}};

    // move引用了horseMoves
    for (const auto &move : horseMoves)
    {
        // 根据马的初始位置计算马的攻击范围
        int nx = x2 + move[0];
        int ny = y2 + move[1];

        // 判定是否越界
        if (nx >= 0 && nx <= x1 && ny >= 0 && ny <= y1)
        {
            data[nx][ny] = 0;
        }
    }

    for (int i = 0; i <= x1; i++)
    {
        for (int j = 0; j <= y1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue; // 这里是起点
            }
            if (data[i][j] == 0)
            {
                continue; // 有障碍的点，没法通过
            }
            if (i == 0)
            {
                data[i][j] = data[i][j - 1]; // 第一行，只能从左来
            }
            else if (j == 0)
            {
                data[i][j] = data[i - 1][j]; // 第一列，只能从上来
            }

            else
            {
                data[i][j] = data[i - 1][j] + data[i][j - 1]; // 可以从上方或者左方来
            }
        }
    }
    std::cout << "路径条数为：" << data[x1][y1] << std::endl;
}
int main()
{
    std::cout << "请输入B点坐标:" << std::endl;
    int x1, y1;
    std::cin >> x1 >> y1;
    AToB(x1, y1);
    std::cout << "请输入马的坐标:" << std::endl;
    int x2, y2;
    std::cin >> x2 >> y2;
    HaveHorse(x1, y1, x2, y2);
    return 0;
}
