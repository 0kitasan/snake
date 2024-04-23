#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <utility>
#include <vector>

namespace snake {

class Snake {
private:
    // 为了方便，直接使用stl(vector)来存储蛇身位置
    std::vector<std::pair<int, int>> snake_body;

public:
    int screen_width = 1000;
    int screen_height = 600;
    int pixel_width = 5;
    int pixel_height = 5;
    int fps = 10;
    int dx=0;
    int dy=0;
    int food_x=0;
    int food_y=0;

    void init_game(); // 考虑直接使用构造函数而不是Init()
    void draw(SDL_Renderer* renderer);
    //需要画出snakebody/food/背景/边界

    void move_forward(int &dx,int &dy);
    void gen_food();
    void logic();
    // 包括是否吃到食物/蛇是否越界
    void cmd_cvt();

    Snake() {
        snake_body.emplace_back(screen_width / 2, screen_height / 2) ;
        // 这里不需要使用std::make_pair()，emplace_back似乎会自动加上
        std::cout << "Constructor called" << std::endl;
    }

    ~Snake() {
        std::cout << "Destructor called" << std::endl;
    }
};
} // namespace snake

#endif // SNAKE_HPP
