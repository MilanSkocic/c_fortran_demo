cmake_minimum_required(VERSION 3.10)

project(program LANGUAGES "C" "Fortran")

set(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} -std=f2003 -Wall")
set(CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS_RELEASE} -std=f2003 -O3")

add_executable(${PROJECT_NAME} main.f90)
