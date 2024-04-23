cmake_minimum_required(VERSION 3.10)
project(snake)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 包含头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 查找 ncurses 库
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# 链接 ncurses 库
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})