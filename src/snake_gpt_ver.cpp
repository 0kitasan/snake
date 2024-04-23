#include <iostream>
#include <SDL.h>
#include <vector>

// 游戏界面相关参数
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = 20;

// 贪吃蛇相关参数
struct SnakeSegment {
    int x, y;
};

std::vector<SnakeSegment> snake;
int foodX, foodY;
int dx = 1, dy = 0;

// 初始化游戏
void initGame() {
    snake.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    foodX = rand() % (SCREEN_WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
    foodY = rand() % (SCREEN_HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;
}

// 绘制游戏界面
void draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // 绘制贪吃蛇
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // 绿色
    for (const auto& segment : snake) {
        SDL_Rect rect = {segment.x, segment.y, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }

    // 绘制食物
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
    SDL_Rect rect = {foodX, foodY, BLOCK_SIZE, BLOCK_SIZE};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

// 处理键盘输入
void handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                dx = 0; dy = -1; break;
            case SDLK_DOWN:
                dx = 0; dy = 1; break;
            case SDLK_LEFT:
                dx = -1; dy = 0; break;
            case SDLK_RIGHT:
                dx = 1; dy = 0; break;
        }
    }
}

// 更新游戏逻辑
void update() {
    int newX = snake.front().x + dx * BLOCK_SIZE;
    int newY = snake.front().y + dy * BLOCK_SIZE;

    // 检查是否吃到食物
    if (newX == foodX && newY == foodY) {
        snake.push_back({foodX, foodY});
        foodX = rand() % (SCREEN_WIDTH / BLOCK_SIZE) * BLOCK_SIZE;
        foodY = rand() % (SCREEN_HEIGHT / BLOCK_SIZE) * BLOCK_SIZE;
    } else {
        // 移动贪吃蛇
        snake.pop_back();
        snake.insert(snake.begin(), {newX, newY});
    }
}

int main() {
    // 初始化SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // 初始化游戏
    initGame();

    // 游戏主循环
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            handleInput(event);
        }

        // 更新游戏逻辑
        update();

        // 绘制游戏界面
        draw(renderer);

        SDL_Delay(100);
    }

    // 退出SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
