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
    if (x2 + 2 <= x1 && y2 - 1 >= 0)
    {
        data[x2 + 2][y2 - 1] = 0;
    }
    if (x2 + 2 <= x1 && y2 + 1 <= y1)
    {
        data[x2 + 2][y2 + 1] = 0;
    }
    if (x2 + 1 <= x1 && y2 + 2 <= y1)
    {
        data[x2 + 1][y2 + 2] = 0;
    }
    if (x2 - 1 >= 0 && y2 + 2 <= y1)
    {
        data[x2 - 1][y2 + 2] = 0;
    }
    if (x2 - 2 >= 0 && y2 + 1 <= y1)
    {
        data[x2 - 2][y2 + 1] = 0;
    }
    if (x2 - 2 >= 0 && y2 - 1 >= 0)
    {
        data[x2 - 2][y2 - 1] = 0;
    }
    if (x2 - 1 >= 0 && y2 - 2 >= 0)
    {
        data[x2 - 1][y2 - 2] = 0;
    }
    if (x2 + 1 <= x1 && y2 - 2 >= 0)
    {
        data[x2 + 1][y2 - 2] = 0;
    }

    for (int i = 0; i <= x1; i++)
    {
        for (int j = 0; j <= y1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            if (data[i][j] == 0)
            {
                continue;
            }
            if (i == 0)
            {
                data[i][j] = data[i][j - 1];
            }
            else if (j == 0)
            {
                data[i][j] = data[i - 1][j];
            }

            else
            {
                data[i][j] = data[i - 1][j] + data[i][j - 1];
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
