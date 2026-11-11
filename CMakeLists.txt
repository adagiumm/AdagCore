cmake_minimum_required(VERSION 3.21)

project(AdagCore
        VERSION 0.1.0
        DESCRIPTION "Cross-platform system resource monitor"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_SOURCES src/platform/linux/platform.c)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_SOURCES src/platform/windows/platform.c)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_SOURCES src/platform/macos/platform.c)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

add_executable(AdagCore
        src/main.c
        ${PLATFORM_SOURCES}
)

target_include_directories(AdagCore PRIVATE include)