#include "snake.hpp"

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
    SDL_Rect rect = { 3, 3, pixel_width, pixel_height };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void snake::Snake::move_forward() {
    snake_body.pop_back(); // 删除最后一个元素
     // 在最前面插入新元素，沿着原来的方向
    snake_body.insert(snake_body.begin(), snake_body.back());
}
