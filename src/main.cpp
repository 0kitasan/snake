#include "snake.cpp"

int main() {
    snake::Snake test_snake;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(test_snake.screen_width,
                                test_snake.screen_height,
                                0,
                                &window,
                                &renderer);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // 绘制游戏界面
        test_snake.draw(renderer);

        SDL_Delay(100);
    }

    // 退出SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
