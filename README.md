# C++大作业：贪吃蛇游戏

SJTU程序设计（C++）课程大作业-陈谐老师班级。

大致思路：

* 初始化
* 绘制初始界面
* while(游戏未结束)
  * 监听输入
  * 检测输入是否冲突/是否吃到食物/是否越界
  * 蛇沿着原先的方向移动

出于跨平台的考虑，目前项目采用SDL库。

为了方便，项目使用stl(vector)来存储蛇身位置

但可能链表更高效一点，下面是一些想法：

```c++
struct Node {
  int x;
  int y;
  Node *next;
};
void AddEnd();
void MoveToFirst();
// 可以用链表存储蛇
// 如果要更新蛇的位置，只需要把尾部元素挪到第一个即可
```

5/9更新

由于SDL太恶心，将项目迁移至了opencv

但是opencv有个问题，就是`cv::waitKey`函数的参数是最大延迟时间，而不是监听时间，
并且它和`std::this_thread::sleep_for`好像并不兼容。因此目前并没有很好的办法解决，
各位就当作这个游戏可以调速吧（笑）。

然后终于完成了检测输入是否冲突的功能，之前一直有bug

写了个程序来检测`cv::waitKey`对于上下左右键的返回值，因此现在已支持使用上下左右，而不仅仅是wasd
screen_img.setTo(cv::Scalar(100, 100, 100));
        snake_game.input_cmd_cvt();
        snake_game.gameover_logic(); // 写成一个单独的函数是为了调试方便
        snake_game.logic_process();
        // 理应先进行逻辑处理，再画出图像
        snake_game.draw();
        snake_game.debug_info();

``` mermaid
graph TD;
    Start --> InitializeGame[（隐式地）加载参数<br>fps,width,height,unit_size];
    InitializeGame --> MainLoop[主循环];
    InputCommand[input_cmd_cvt<br>cv::waitKey];
    CheckGameOver[gameover_logic<br>撞倒自身或边界];
    ProcessLogic[logic_process
                  检测输入冲突
                  吃到食物:grow_and_move
                  没吃到:move_forward];
    DrawGame[draw];
    MainLoop --> InputCommand
    InputCommand -->|direction_cvt| CheckGameOver;
    CheckGameOver -->|游戏未失败| ProcessLogic;
    ProcessLogic --> DrawGame;
    CheckGameOver -->|游戏失败| QuitGame;
    DrawGame -->|进入下次循环| MainLoop;
```

