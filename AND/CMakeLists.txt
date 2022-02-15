cmake_minimum_required(VERSION 3.20)
project(AND)

set(CMAKE_CXX_STANDARD 17)

add_executable(AND main.cpp
        src/Matrix.h
        src/Network.cpp
        src/Network.h
        src/DataSet.cpp
        src/DataSet.h src/MoveMapper.cpp src/MoveMapper.h src/MoveParser.cpp src/MoveParser.h)
