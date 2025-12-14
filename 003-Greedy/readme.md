# 003-Greedy

## 简介

- 贪心算法示例，添加了最小堆操作。

## 需求

### 题目描述：有n个人排队到r个水龙头前去打水，他们装满水桶的时间分别为t1,t2,t3,…,tn，打水时间均为整数且各不相等，应该如何安排他们的打水顺序才能使他们花费的总时间最少？每个人的打水时间=排队时间+装满水桶的时间(假设排队切换等其他过程均不消耗时间)

### 要求程序

- 输入：有两行，第1行为两个整数，分别是n和r,即人数和水龙头数。
(1<=n<=500)(1<=r<=100)
- 第二行为n个正整数t1,t2,t3,…,ti(1<=ti<=1000)。表示每个人装满水桶的时间
- 输出：1行，一个正整数，表示他们花费的最少总时间。

## 代码解释

```c++
/// 使用&引用
void getWater(int per, int num, std::vector<int> &time)

 std::priority_queue<int, std::vector<int>, std::greater<int>>
 // std::priority_queue<队列元素类型, 底层容器类型, 比较函数类型>

 // 默认情况：最大堆（不加第三个参数）
// std::priority_queue<int> max_heap;
// 等价于：
// std::priority_queue<int, std::vector<int>, std::less<int>> max_heap;
// std::less<int>：元素越大，优先级越高,堆顶是最大值
// std::gregreater<int>: 元素越小，优先级越高,堆顶是最小值
```
