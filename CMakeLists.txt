cmake_minimum_required(VERSION 3.13)
project(redblack)

set(CMAKE_CXX_STANDARD 14)

add_executable(redblack main.cpp Node.cpp Node.h RedBlackTree.cpp RedBlackTree.h)