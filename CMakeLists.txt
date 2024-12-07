cmake_minimum_required(VERSION 3.29)
project(cache_performance C)

set(CMAKE_C_STANDARD 23)

set(PROJECT_HEADER config.h)
set(PROJECT_SOURCE main.c)

add_executable(${PROJECT_NAME} ${PROJECT_HEADER} ${PROJECT_SOURCE})