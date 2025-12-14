#include "main.h"
#include <algorithm>
#include <vector>
#include <queue>

/**
 * 计算最少时间
 * @param per 人数
 * @param num 水龙头数
 * @param time 每个人打水时间
 */
void getWater(int per, int num, std::vector<int> &time)
{
    // 排序，将最少的时间排在前
    std::sort(time.begin(), time.end());

    // 创建最小堆用于用于寻找最早空闲的水龙头
    std::priority_queue<int, std::vector<int>, std::greater<int>> water_taps;

    // 先将水龙头时间都调整为0
    for (int i = 0; i < num; i++)
    {
        water_taps.push(0);
    }
    // 总时间计数
    int total_time = 0;

    for (int i = 0; i < per; i++)
    {
        // 读取堆顶（最早空闲的水龙头）时间
        int earliest = water_taps.top();
        water_taps.pop(); // 弹出堆顶

        // 这个人花费的时间 = 等待时间 + 打水时间
        int per_time = earliest + time[i];

        // 累加总时间
        total_time += per_time;

        // 更新水龙头时间（下一个使用水龙头的人时间在前一个人的时间上累加）
        water_taps.push(per_time);
    }
    std::cout << "总时间为：" << total_time << std::endl;
}
int main()
{
    int r, n, s = 0;
    std::cout << "请输入人数和水龙头数：" << std::endl;
    std::cin >> n >> r;
    std::vector<int> data(n);
    std::cout << "请输入" << n << "个人的打水时间：" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> data[i];
    }
    getWater(n, r, data);

    return 0;
}
