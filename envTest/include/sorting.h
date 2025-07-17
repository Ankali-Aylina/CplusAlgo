#pragma once
#include <vector>
#include <functional> // 添加这个头文件

template <typename T>
void quick_sort(std::vector<T> &arr)
{
    // 声明 std::function 类型
    std::function<int(int, int)> partition;
    std::function<void(int, int)> quicksort;

    // 定义 partition
    partition = [&](int low, int high) -> int
    {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    };

    // 定义 quicksort
    quicksort = [&](int low, int high)
    {
        if (low < high)
        {
            int pi = partition(low, high);
            quicksort(low, pi - 1);
            quicksort(pi + 1, high);
        }
    };

    quicksort(0, arr.size() - 1);
}
