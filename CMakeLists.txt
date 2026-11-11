cmake_minimum_required(VERSION 3.21)

project(AdagCore
        VERSION 0.1.0
        DESCRIPTION "Cross-platform system resource monitor"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(AdagCore main.c)