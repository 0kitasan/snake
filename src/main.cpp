#include "snake.cpp"

int main() {
    snake::Snake test_snake;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_width,
                                screen_height,
                                0,
                                &window,
                                &renderer);

    bool quit = false;
    test_snake.gen_food();
    SDL_Event event;
    while (!quit) {
        test_snake.draw(renderer);
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true; 
            }
            test_snake.input_cmd_cvt(event);
        }
        test_snake.logic_process();
        SDL_Delay(test_snake.fps);
    }

    // 退出SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
