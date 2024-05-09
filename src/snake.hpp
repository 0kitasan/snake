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
int frame = 0;
int pressed_time = 0;
const int UNIT_SIZE = 20;
int screen_width_n = 40;
int screen_height_n = 25;
int screen_width = UNIT_SIZE * screen_width_n;
int screen_height = UNIT_SIZE * screen_height_n;
const int FPS = 5;
const int DELAY = 1000 / FPS; // 单位是ms
// @todo:可以定义color结构体，设为全局变量以调控颜色
cv::Mat screen_img(screen_height, screen_width, CV_8UC3, cv::Scalar(0, 0, 0));
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };
// 对于Direction枚举类型，重载输出运算符
std::ostream& operator<<(std::ostream& os, const Direction& dir) {
    switch (dir) {
        case Direction::NONE:
            os << "NONE";
            break;
        case Direction::UP:
            os << "UP";
            break;
        case Direction::DOWN:
            os << "DOWN";
            break;
        case Direction::LEFT:
            os << "LEFT";
            break;
        case Direction::RIGHT:
            os << "RIGHT";
            break;
    }
    return os;
}
namespace snake {

class Snake {
private:
    // 为了方便，直接使用stl(vector)来存储蛇身位置
    std::vector<std::pair<int, int>> snake_body;
    int dx = 0;
    int dy = 0;
    Direction input_dir = Direction::NONE;
    Direction move_dir = Direction::NONE;
    void gen_food();
    void direction_cvt();
    void move_forward();
    void grow_and_move();

public:
    int direction[2];
    int direction_buf[2];
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
