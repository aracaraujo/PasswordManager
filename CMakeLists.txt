cmake_minimum_required(VERSION 3.23)
project(password_manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(password_manager main.cpp Dice.h Dice.cpp Password.h Password.cpp Account.h Account.cpp)
