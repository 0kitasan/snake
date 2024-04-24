#include "snake.cpp"
#include "snake.hpp"
#include <chrono>
#include <thread>

int main() {
    snake::Snake test_snake;

    while (true) {
        screen_img.setTo(cv::Scalar(100, 100, 100));
        if (!test_snake.input_cmd_cvt()) {
            break;
        }
        test_snake.draw();
        test_snake.logic_process();
        test_snake.debug_info();

        // 显示图像
        cv::imshow("Snake Game", screen_img);

        // auto start = std::chrono::steady_clock::now();

        // auto end = std::chrono::steady_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // std::this_thread::sleep_for(std::chrono::milliseconds(DELAY) - duration);
    }

    cv::destroyAllWindows();

    return 0;
}
