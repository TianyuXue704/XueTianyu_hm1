cmake_minimum_required(VERSION 3.10)
project(XueTianyu_hm1 LANGUAGES C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(inc)

# 收集源代码文件
file(GLOB SRC_FILES
    src/*.c
)

# 生成可执行文件
add_executable(algebra_app
    ${SRC_FILES}
)