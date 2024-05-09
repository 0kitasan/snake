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
    // 绘制边界
    for (int x = 0; x < screen_width_n; x++) {
        cv::rectangle(screen_img,
                      cv::Rect(x * UNIT_SIZE, 0, UNIT_SIZE, UNIT_SIZE),
                      cv::Scalar(255, 255, 255),
                      -1);
        cv::rectangle(screen_img,
                      cv::Rect(x * UNIT_SIZE,
                               (screen_height_n - 1) * UNIT_SIZE,
                               10 * UNIT_SIZE,
                               10 * UNIT_SIZE),
                      cv::Scalar(255, 255, 255),
                      -1);
    }
}

void snake::Snake::direction_cvt() {
    switch (move_dir) {
        case Direction::NONE:
            dx = 0;
            dy = 0;
            break;
        case Direction::UP:
            dx = 0;
            dy = -1;
            break;
        case Direction::DOWN:
            dx = 0;
            dy = 1;
            break;
        case Direction::LEFT:
            dx = -1;
            dy = 0;
            break;
        case Direction::RIGHT:
            dx = 1;
            dy = 0;
            break;
        default:
            break;
    }
}

void snake::Snake::move_forward() {
    snake_body.pop_back(); // 删除最后一个元素
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
}

void snake::Snake::grow_and_move() {
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
}

void snake::Snake::gen_food() {
    // 通过种子生成伪随机数
    srand(time(nullptr));
    food_x = rand() % (screen_width_n - 2);
    food_y = rand() % (screen_height_n - 2);
    std::pair<int, int> food_pos = std::make_pair(food_x + 1, food_y + 1);
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

    if (condition1 && condition2) {
        grow_and_move();
        gen_food();
        score++;
    } else {
        move_forward();
    }
}

bool snake::Snake::input_cmd_cvt() {
    bool result = true;
    int key = cv::waitKey(DELAY); // 等待键盘输入
    if (key == 'q' || key == 27) {
        // 按下q或esc，则退出循环
        // @todo：还需要完善
        // 通过cv的关闭键来关闭页面
        result = false;
    } else if (key == 'w' || key == 'W') {
        input_dir = Direction::UP;
    } else if (key == 's' || key == 'S') {
        input_dir = Direction::DOWN;
    } else if (key == 'a' || key == 'A') {
        input_dir = Direction::LEFT;
    } else if (key == 'd' || key == 'D') {
        input_dir = Direction::RIGHT;
    }
    if (score < 1) {
        move_dir = input_dir;
        direction_cvt();
    } else {
        // 如果input_dir和move_dir产生冲突，move_dir需要保持原来的值
        bool condition1 = (move_dir == Direction::DOWN) && (input_dir == Direction::UP);
        bool condition2 = (move_dir == Direction::UP) && (input_dir == Direction::DOWN);
        bool condition3 = (move_dir == Direction::LEFT) && (input_dir == Direction::RIGHT);
        bool condition4 = (move_dir == Direction::RIGHT) && (input_dir == Direction::LEFT);
        if (condition1 || condition2 || condition3 || condition4) {
            return result;
        } else {
            move_dir = input_dir;
            direction_cvt();
        }
    }
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
    // 对于Direction枚举类型，重载了输出运算符
    direction_ss << "snake direction= " << move_dir;
    std::string direction = direction_ss.str();

    std::stringstream direction_buf_ss;
    // direction_buf_ss << "snake direction buffer= " << dir_cache.front();
    direction_buf_ss << "input direction= " << input_dir;
    std::string direction_buf = direction_buf_ss.str();

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
