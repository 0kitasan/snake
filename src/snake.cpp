#include "snake.hpp"
#include <sstream>
#include <string>
#include <thread>
#include <utility>

void snake::Snake::draw() {
    for (auto body: snake_body) {
        cv::rectangle(
            screen_img,
            cv::Rect(body.first * UNIT_SIZE, body.second * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE),
            cv::Scalar(0, 255, 0),
            -1);
    }
    cv::rectangle(screen_img,
                  cv::Rect(snake_body.begin()->first * UNIT_SIZE,
                           snake_body.begin()->second * UNIT_SIZE,
                           UNIT_SIZE,
                           UNIT_SIZE),
                  cv::Scalar(0, 255, 255),
                  -1);
    cv::rectangle(screen_img,
                  cv::Rect(food_x * UNIT_SIZE, food_y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE),
                  cv::Scalar(0, 0, 255),
                  -1);
    for (int x = 0; x < screen_width_n; x++) {
        cv::rectangle(screen_img,
                      cv::Rect(x * UNIT_SIZE, 0, UNIT_SIZE, UNIT_SIZE),
                      cv::Scalar(0, 255, 0),
                      -1);
        cv::rectangle(
            screen_img,
            cv::Rect(x * UNIT_SIZE, screen_height_n * UNIT_SIZE, 10 * UNIT_SIZE, 10 * UNIT_SIZE),
            cv::Scalar(0, 255, 0),
            -1);
    }
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
    // 通过种子生成伪随机数
    srand(time(nullptr));
    food_x = rand() % screen_width_n;
    food_y = rand() % screen_height_n;
    std::pair<int, int> food_pos = std::make_pair(food_x, food_y);
    //这里要确保food和snake不重合
    // for (auto body: snake_body) {
    //     if (body == food_pos) {
    //         gen_food();
    //     }
    // }
}

void snake::Snake::logic_process() {
    //检测是否吃到食物
    int snake_head_x = snake_body.begin()->first;
    int snake_head_y = snake_body.begin()->second;
    bool condition1 = (food_x == snake_head_x);
    bool condition2 = (food_y == snake_head_y);

    bool condition3 = (dir_buf[2] == -dir_buf[0]) && (dir_buf[3] == dir_buf[1]);
    bool condition4 = (dir_buf[2] == dir_buf[0]) && (dir_buf[3] == -dir_buf[1]);
    //std::cout << dx_buf << ' ' << dy_buf << std::endl;
    if (condition3 && condition4) {
        move_forward(dir_buf[2], dir_buf[3]);
    } else {
        if (condition1 && condition2) {
            grow_and_move(dx, dy);
            gen_food();
            score++;
        } else {
            move_forward(dx, dy);
        }
    }
}

bool snake::Snake::input_cmd_cvt() {
    bool result = true;
    int key = cv::waitKey(DELAY); // 等待键盘输入
    if (key == 'q' || key == 27) {
        // 按下q或esc，则退出循环
        // @todo
        // cv的关闭键
        result = false;
    } else if (key == 'w' || key == 'W') {
        dx = 0;
        dy = -1;
    } else if (key == 's' || key == 'S') {
        dx = 0;
        dy = 1;
    } else if (key == 'a' || key == 'A') { // 按下 'a' 或 'A' 键
        dx = -1;
        dy = 0;
    } else if (key == 'd' || key == 'D') { // 按下 'd' 或 'D' 键
        dx = 1;
        dy = 0;
    }
    // 这地方写的太抽象了，需要修改
    dir_buf[2] = dir_buf[0];
    dir_buf[3] = dir_buf[1];
    dir_buf[0] = dx;
    dir_buf[1] = dy;
    return result;
}

void snake::Snake::debug_info() {
    std::stringstream snake_pos_ss;
    snake_pos_ss << "snake_pos= " << snake_body.begin()->first << ' ' << snake_body.begin()->second;
    std::string snake_pos = snake_pos_ss.str();

    std::stringstream food_pos_ss;
    food_pos_ss << "food_pos= " << food_x << ' ' << food_y;
    std::string food_pos = food_pos_ss.str();

    std::stringstream direction_ss;
    direction_ss << "snake direction= " << dx << ' ' << dy;
    std::string direction = direction_ss.str();

    std::stringstream direction_buf_ss;
    direction_buf_ss << "snake direction= " << dir_buf[2] << ' ' << dir_buf[3];
    std::string direction_buf = direction_ss.str();

    std::string score_text = "score= " + std::to_string(score);

    cv::putText(screen_img,
                snake_pos,
                cv::Point(10, 30),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                food_pos,
                cv::Point(10, 60),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                direction,
                cv::Point(10, 90),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                score_text,
                cv::Point(10, 120),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                direction_buf,
                cv::Point(10, 150),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(255, 0, 0),
                2);
}
