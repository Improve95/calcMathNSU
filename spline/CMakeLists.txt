cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(calcMath)
set(exe_name ${PROJECT_NAME})

add_executable(calcMath spline.cpp)