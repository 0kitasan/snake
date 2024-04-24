#include "snake.hpp"
#include <utility>

void snake::Snake::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 绘制贪吃蛇
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 绿色
    for (auto it: snake_body) {
        SDL_Rect rect = { it.first*unit_size, it.second*unit_size, unit_size, unit_size};
        SDL_RenderFillRect(renderer, &rect);
    }

    // 绘制食物
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
    SDL_Rect rect = { food_x*unit_size, food_y*unit_size, unit_size, unit_size };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void snake::Snake::move_forward(int& dx, int& dy) {
    snake_body.pop_back(); // 删除最后一个元素
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
}

void snake::Snake::grow_and_move(int& dx, int& dy) {
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
}

void snake::Snake::gen_food() {
    srand(time(nullptr));
    food_x = rand() % screen_width_n;
    food_y = rand() % screen_height_n;
    std::cout<<"food pos:"<<food_x<<' '<<food_y<<std::endl;
    std::pair<int, int> food_pos = std::make_pair(food_x, food_y);
    //这里要确保food和snake不重合
    // for (auto body: snake_body) {
    //     if (body == food_pos) {
    //         gen_food();
    //     }
    // }
}

void snake::Snake::print_body() {
    for (auto it: snake_body) {
        std::cout<<it.first<<' '<<it.second<<std::endl;
    }
}

void snake::Snake::logic_process() {
    //检测是否吃到食物
    int snake_head_x = snake_body.begin()->first;
    int snake_head_y = snake_body.begin()->second;
    bool condition1 =
        (food_x - unit_size/10 < snake_head_x) && (snake_head_x < food_x + unit_size/10);
    bool condition2 =
        (food_y - unit_size/10 < snake_head_y) && (snake_head_y < food_x + unit_size/10);
    if (condition1 && condition2) {
        std::cout<<"food eaten!"<<std::endl;
        grow_and_move(dx, dy);
        gen_food();
        print_body();
    } else {
        move_forward(dx, dy);
    }
}

void snake::Snake::input_cmd_cvt(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                dx = 0;
                dy = -1;
                break;
            case SDLK_DOWN:
                dx = 0;
                dy = 1;
                break;
            case SDLK_LEFT:
                dx = -1;
                dy = 0;
                break;
            case SDLK_RIGHT:
                dx = 1;
                dy = 0;
                break;
        }
    }
}

void snake::Snake::debug_info(){

}
