#include "snake.hpp"

void snake::Snake::Draw() {
  // 可能还需要绘制边界
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      std::cout << '-';
    }
    std::cout << std::endl;
  }
}
