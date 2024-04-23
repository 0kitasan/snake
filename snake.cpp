#include "snake.hpp"

void snake::Snake::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // 绘制贪吃蛇
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 绿色
    for (auto it : snake_body) {
        SDL_Rect rect = {it.first, it.second, 1, 1};
        SDL_RenderFillRect(renderer, &rect);
    }

    // 绘制食物
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
    SDL_Rect rect = {3, 3, 1, 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}
