cmake_minimum_required(VERSION 3.10)

# set the project name
project(progcmake VERSION 1.0)

# add the executable
add_executable(${PROJECT_NAME} main.c tokenobject.c lexerobject.c parser.c)

# configuration header
configure_file(version.h.in version.h)

# directories
include_directories(${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")




