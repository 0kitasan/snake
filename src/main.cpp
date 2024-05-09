#include "snake.cpp"
#include "snake.hpp"
#include <chrono>
#include <thread>

int main() {
    snake::Snake snake_game;

    while (!game_over && !game_quit) {
        screen_img.setTo(cv::Scalar(100, 100, 100));
        snake_game.input_cmd_cvt();
        snake_game.gameover_logic(); // 写成一个单独的函数是为了调试方便
        snake_game.logic_process();
        // 理应先进行逻辑处理，再画出图像
        snake_game.draw();
        snake_game.debug_info();

        // 显示图像
        cv::imshow("Snake Game(Press 'q' or 'ESC' to quit)", screen_img);

        // auto start = std::chrono::steady_clock::now();
        // auto end = std::chrono::steady_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // std::this_thread::sleep_for(std::chrono::milliseconds(DELAY) - duration);
    }

    cv::destroyAllWindows();

    return 0;
}
