cmake_minimum_required(VERSION 3.20)
project(ChessAnalytics)

set(CMAKE_CXX_STANDARD 20)
set(Eigen3_DIR D:\\Libs\\eigen-3.4.0\\cmake)

find_package(Eigen3 3.4 REQUIRED NO_MODULE)

add_library(ChessAnalytics SHARED main.cpp)
target_link_libraries(ChessAnalytics Eigen3::Eigen)
