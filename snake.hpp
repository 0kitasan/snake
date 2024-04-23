#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <SDL2/SDL.h>

namespace snake {

class Snake {

private:
  int fps = 10;
  
  // 为了方便，直接使用stl(vector)来存储蛇身位置
  std::vector<std::pair<int, int>> snake_body;

public:
  int width = 500;
  int height = 200;
  void Init(); // 考虑直接使用构造函数而不是Init()
  void Draw(SDL_Renderer* renderer); 
  /*
  @todo 需要画出snakebody/food/背景/边界
  */
  
  void Move() {
    snake_body.insert(
        snake_body.begin(),
        snake_body.back()); // 将最后一个元素插入到第一个位置
    snake_body.pop_back();  // 删除最后一个元素
  };

  void GenFood();

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

