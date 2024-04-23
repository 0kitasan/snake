# snake
Snake Game for Cpp homework in SJTU

``` c++
struct Node {
  int x;
  int y;
  Node *next;
};
void AddEnd();
void MoveToFirst();
// 可以用链表存储蛇
// 如果要更新蛇的位置，只需要把尾部元素挪到第一个即可
```

大致思路：

初始化
绘制初始界面
while(游戏未结束)
监听输入
蛇沿着原先的方向移动
检测是否吃到食物
检测是否越界
