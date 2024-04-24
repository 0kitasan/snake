#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <utility>
#include <vector>

// 全局变量
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
SDL_Texture* score_texture;
int score = 0;
int unit_size = 20;
int screen_width_n = 40;
int screen_height_n = 25;
int screen_width = unit_size * screen_width_n;
int screen_height = unit_size * screen_height_n;

namespace snake {

// bool init_sdl() {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         return false;
//     }
//     if (TTF_Init() == -1) {
//         return false;
//     }
//     window = SDL_CreateWindow("Snake Game",
//                               SDL_WINDOWPOS_CENTERED,
//                               SDL_WINDOWPOS_CENTERED,
//                               screen_width,
//                               screen_height,
//                               SDL_WINDOW_SHOWN);
//     if (window == nullptr) {
//         return false;
//     }
//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (renderer == nullptr) {
//         return false;
//     }
//     return true;
// }

class Snake {
private:
    // 为了方便，直接使用stl(vector)来存储蛇身位置
    std::vector<std::pair<int, int>> snake_body;
    void print_body();

public:
    int fps = 80;

    int dx = 0;
    int dy = 0;
    int food_x = 0;
    int food_y = 0;

    void init_game(); // 考虑直接使用构造函数而不是Init()
    void draw(SDL_Renderer* renderer);
    //需要画出snakebody/food/背景/边界

    void move_forward(int& dx, int& dy);
    void grow_and_move(int& dx, int& dy);

    void gen_food();
    void logic_process();
    // 包括是否吃到食物/蛇是否越界
    void input_cmd_cvt(SDL_Event& event);

    void debug_info();

    Snake() {
        snake_body.emplace_back(screen_width_n / 2, screen_height_n / 2);
        // 这里不需要使用std::make_pair()，emplace_back似乎会自动加上
        std::cout << "Constructor called" << std::endl;
    }

    ~Snake() {
        std::cout << "Destructor called" << std::endl;
    }
};
} // namespace snake

#endif // SNAKE_HPP
