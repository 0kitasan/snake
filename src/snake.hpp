#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

// 全局变量
int score = 0;
const int UNIT_SIZE = 20;
int screen_width_n = 40;
int screen_height_n = 25;
int screen_width = UNIT_SIZE * screen_width_n;
int screen_height = UNIT_SIZE * screen_height_n;
const int FPS = 5;
const int DELAY = 1000 / FPS; // 单位是ms
cv::Mat screen_img(screen_height, screen_width, CV_8UC3, cv::Scalar(0, 0, 0));

namespace snake {

class Snake {
private:
    // 为了方便，直接使用stl(vector)来存储蛇身位置
    std::vector<std::pair<int, int>> snake_body;
    int dir_buf[4] = { 0 };
    void gen_food();
    void move_forward(int& dx, int& dy);
    void grow_and_move(int& dx, int& dy);

public:
    int dx = 0;
    int dy = 0;
    int food_x = 0;
    int food_y = 0;
    int score = 0;

    void init_game(); // 考虑直接使用构造函数而不是Init()
    void draw();
    //需要画出snakebody/food/背景/边界

    void logic_process();
    // 包括是否吃到食物/蛇是否越界
    bool input_cmd_cvt();

    void debug_info();

    Snake() {
        snake_body.emplace_back(screen_width_n / 2, screen_height_n / 2);
        // 这里不需要使用std::make_pair()，emplace_back似乎会自动加上
        gen_food();
        std::cout << "Constructor called" << std::endl;
    }

    ~Snake() {
        std::cout << "Destructor called" << std::endl;
    }
};
} // namespace snake

#endif // SNAKE_HPP
