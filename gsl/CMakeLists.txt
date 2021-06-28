cmake_minimum_required(VERSION 3.10)

project(test_gsl C)

set(CMAKE_C_STANDARD 99)

add_compile_options("-O3")

add_executable(test_gsl main.c)
target_link_directories(test_gsl PRIVATE /usr/lib/x86_64-linux-gnu)
target_link_libraries(test_gsl PRIVATE m gsl openblas)
