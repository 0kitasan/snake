#include "snake.hpp"
#include <utility>

void snake::Snake::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 绘制贪吃蛇
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 绿色
    for (auto it: snake_body) {
        SDL_Rect rect = { it.first, it.second, pixel_width, pixel_height };
        SDL_RenderFillRect(renderer, &rect);
    }

    // 绘制食物
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
    SDL_Rect rect = { food_x, food_y, pixel_width, pixel_height };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void snake::Snake::move_forward(int& dx, int& dy) {
    snake_body.pop_back(); // 删除最后一个元素
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_x = snake_body.begin()->first + dx;
    int snake_head_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_renew = std::make_pair(snake_head_x, snake_head_y);
    snake_body.insert(snake_body.begin(), snake_head_renew);
}

void snake::Snake::gen_food() {
    food_x = rand() % (screen_width / pixel_width) * pixel_width;
    food_y = rand() % (screen_height / pixel_height) * pixel_height;
    //这里要确保food和snake不重合
}