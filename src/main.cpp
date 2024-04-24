#include "snake.cpp"
#include "snake.hpp"

int main() {
    snake::Snake test_snake;
    
    while (true) {
        screen_img.setTo(cv::Scalar(0, 0, 0));
        test_snake.logic_process();
        test_snake.draw();
        test_snake.debug_info();
        // 显示图像
        cv::imshow("Snake Game", screen_img);

        if (!test_snake.input_cmd_cvt()) { 
            break;
        }
    }

    return 0;
}
