#include "main.h"
#include <vector>
#include <chrono>

void testPerformance()
{
    const int ROWS = 10000;
    const int COLS = 1000;

    // 方法1：不预分配（性能较差）
    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> matrix1;
    for (int i = 0; i < ROWS; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < COLS; j++)
        {
            row.push_back(j);
        }
        matrix1.push_back(row);
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // 方法2：预分配内存（性能更好）
    auto start2 = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> matrix2;
    matrix2.reserve(ROWS); // 预分配行数

    for (int i = 0; i < ROWS; i++)
    {
        std::vector<int> row;
        row.reserve(COLS); // 预分配每行的列数
        for (int j = 0; j < COLS; j++)
        {
            row.push_back(j);
        }
        matrix2.push_back(std::move(row)); // 使用移动语义
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    // 计算时间差
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "不预分配: " << duration1.count() << " ms" << std::endl;
    std::cout << "预分配: " << duration2.count() << " ms" << std::endl;
}

int main()
{
    testPerformance();
    return 0;
}
