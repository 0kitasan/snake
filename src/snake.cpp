#include "snake.hpp"
#include <opencv2/highgui.hpp>
#include <random>
#include <sstream>
#include <string>
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
    for (int y = 0; y < screen_width_n; y++) {
        cv::rectangle(screen_img,
                      cv::Rect(0, y * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE),
                      cv::Scalar(255, 255, 255),
                      -1);
        cv::rectangle(screen_img,
                      cv::Rect((screen_width_n - 1) * UNIT_SIZE,
                               y * UNIT_SIZE,
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
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
    snake_body.pop_back(); // 删除最后一个元素，这一步需要最后做，防止出现未定义行为
}

void snake::Snake::grow_and_move() {
    // 在最前面插入新元素，沿着原来的方向前进一格
    int snake_head_new_x = snake_body.begin()->first + dx;
    int snake_head_new_y = snake_body.begin()->second + dy;
    std::pair<int, int> snake_head_new = std::make_pair(snake_head_new_x, snake_head_new_y);
    snake_body.insert(snake_body.begin(), snake_head_new);
}

void snake::Snake::gen_food() {
    //使用<random>生成随机数
    //这种方法似乎比srand(time(nullptr))更好
    std::random_device rd;
    std::mt19937 gen(rd()); // 使用随机设备生成随机数种子
    // 定义均匀分布的整数随机数生成器
    std::uniform_int_distribution<int> dis_x(1, screen_width_n - 2);
    std::uniform_int_distribution<int> dis_y(1, screen_height_n - 2);
    food_x = dis_x(gen);
    food_y = dis_y(gen);
    std::pair<int, int> food_pos = std::make_pair(food_x, food_y);

    //这里要确保food和snake不重合
    for (auto body: snake_body) {
        if (body == food_pos) {
            // 个人觉得这个方法不是很好，因此将重合次数存储并输出
            food_overlap_time++;
            gen_food();
        }
    }
}
void snake::Snake::gameover_logic() {
    int snake_head_x = snake_body.begin()->first;
    int snake_head_y = snake_body.begin()->second;
    bool condition1 = (snake_head_x == 0) || (snake_head_x == screen_width_n - 1);
    bool condition2 = (snake_head_y == 0) || (snake_head_y == screen_height_n - 1);
    if (condition1 || condition2) {
        game_over = true;
    }
    for (auto it = snake_body.begin() + 1; it != snake_body.end(); ++it) {
        // 检测蛇是否与自身相撞
        auto body = *it;
        if (snake_head_x == body.first && snake_head_y == body.second) {
            game_over = true;
        }
    }
    if (game_over) {
        std::cout << "Game Over~" << std::endl;
    }
}

void snake::Snake::logic_process() {
    // 检测用户输入是否会导致冲突
    if (score < 1) {
        // 没有分数时，无需考虑冲突
        move_dir = input_dir;
        direction_cvt();
    } else {
        // 如果input_dir和move_dir产生冲突，move_dir需要保持原来的值
        bool condition1 = (move_dir == Direction::DOWN) && (input_dir == Direction::UP);
        bool condition2 = (move_dir == Direction::UP) && (input_dir == Direction::DOWN);
        bool condition3 = (move_dir == Direction::LEFT) && (input_dir == Direction::RIGHT);
        bool condition4 = (move_dir == Direction::RIGHT) && (input_dir == Direction::LEFT);
        if (condition1 || condition2 || condition3 || condition4) {
            return;
        } else {
            move_dir = input_dir;
            direction_cvt();
        }
    }

    //检测是否吃到食物
    int snake_head_x = snake_body.begin()->first;
    int snake_head_y = snake_body.begin()->second;
    bool condition5 = (food_x == snake_head_x);
    bool condition6 = (food_y == snake_head_y);
    if (condition5 && condition6) {
        grow_and_move();
        gen_food();
        score++;
    } else {
        move_forward();
    }
}

void snake::Snake::input_cmd_cvt() {
    int key = cv::waitKeyEx(DELAY); // 等待键盘输入
    if (key == 'q' || key == 27 || key==255) {
        // 按下q或esc，则退出循环
        // @todo：还需要完善
        // 通过cv的关闭键来关闭页面
        // 现在看来好像是不太行的，因为按下关闭键/不按任何键
        // cv::waitKey都会返回-1
        game_quit = true;
        std::cout << "quit game, goodbye ..." << std::endl;
    } else if (key == 'w' || key == 'W' || key == 65362) {
        input_dir = Direction::UP;
    } else if (key == 's' || key == 'S' || key == 65364) {
        input_dir = Direction::DOWN;
    } else if (key == 'a' || key == 'A' || key == 65361) {
        input_dir = Direction::LEFT;
    } else if (key == 'd' || key == 'D' || key == 65363) {
        input_dir = Direction::RIGHT;
    }
    frame++;
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
    direction_ss << "move/input direction= " << move_dir << "/" << input_dir;
    std::string direction = direction_ss.str();

    std::string score_text = "score= " + std::to_string(score) + " frame=" + std::to_string(frame);
    std::string food_overlap = "food overlap time= " + std::to_string(food_overlap_time);

    double font_scale = 0.8;
    cv::putText(screen_img,
                snake_pos,
                cv::Point(20, 40),
                cv::FONT_HERSHEY_SIMPLEX,
                font_scale,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                food_pos,
                cv::Point(20, 65),
                cv::FONT_HERSHEY_SIMPLEX,
                font_scale,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                direction,
                cv::Point(20, 90),
                cv::FONT_HERSHEY_SIMPLEX,
                font_scale,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                score_text,
                cv::Point(20, 115),
                cv::FONT_HERSHEY_SIMPLEX,
                font_scale,
                cv::Scalar(255, 0, 0),
                2);
    cv::putText(screen_img,
                food_overlap,
                cv::Point(20, 140),
                cv::FONT_HERSHEY_SIMPLEX,
                font_scale,
                cv::Scalar(255, 0, 0),
                2);
}
