#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <utility>
#include <vector>

namespace snake {

class Snake {

private:
  int fps = 10;
  int width = 50;
  int height = 20;
  // 为了方便，直接使用stl(vector)来存储蛇身位置
  std::vector<std::pair<int, int>> snake_body;

public:
  void Init(); // 考虑直接使用构造函数而不是Init()
  void Draw();
  void Move() {
    snake_body.insert(
        snake_body.begin(),
        snake_body.back()); // 将最后一个元素插入到第一个位置
    snake_body.pop_back();  // 删除最后一个元素
  };

  void Logic();
  // 包括是否吃到食物/蛇是否越界

  void CmdCvt();
  Snake() {
    snake_body.push_back(std::make_pair(width / 2, height / 2));
    std::cout << "Constructor called" << std::endl;
  }
  ~Snake() { std::cout << "Destructor called" << std::endl; }
};
} // namespace snake

#endif // SNAKE_HPP


/*
#include <ncurses.h>

int main() {
    // 初始化 ncurses
    initscr();
    cbreak(); // 禁用行缓冲，使得输入立即可用
    noecho(); // 禁止回显，不显示输入的字符

    printw("Press any key ('q' to quit):\n");
    refresh();

    char ch;
    while (true) {
        // 获取一个字符
        ch = getch();

        // 检查是否按下了 'q' 键，如果是则退出循环
        if (ch == 'q') {
            printw("Exiting...\n");
            break;
        }

        // 显示按下的键
        printw("You pressed: %c\n", ch);
        refresh();
    }

    // 清理 ncurses
    endwin();

    return 0;
}


初始化
绘制初始界面
while(游戏未结束)
监听输入
蛇沿着原先的方向移动
检测是否吃到食物
检测是否越界
*/