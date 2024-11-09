project(opencv-mobile-test)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_C_COMPILER "/home/book/Desktop/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
SET(CMAKE_CXX_COMPILER "/home/book/Desktop/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")

set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv-mobile-4.8.1-luckfox-pico/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv-mobile-test mp4ply.cpp)

target_link_libraries(opencv-mobile-test ${OpenCV_LIBS})