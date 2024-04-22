#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <utility>
#include <vector>

namespace snake {

struct Node {
  int x;
  int y;
  Node *next;
};
void AddEnd();
void MoveToFirst();
// 可以用链表存储蛇
// 如果要更新蛇的位置，只需要把尾部元素挪到第一个即可

class Snake {

private:
  int fps = 10;
  int width = 50;
  int height = 20;
  // 为了方便，直接使用stl(vector)来存储蛇身各点的位置
  std::vector<std::pair<int, int>> snake_position;

public:
  void Init(); // 考虑直接使用构造函数而不是Init()
  void Draw();
  void Move() {
    snake_position.insert(
        snake_position.begin(),
        snake_position.back()); // 将最后一个元素插入到第一个位置
    snake_position.pop_back();  // 删除最后一个元素
  };

  void Logic();
  // 包括是否吃到食物/蛇是否越界

  void CmdCvt();
  Snake() {
    snake_position.push_back(std::make_pair(width / 2, height / 2));
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

*/