cmake_minimum_required(VERSION 3.10)

project("object" VERSION "0.1" LANGUAGES "C")

add_executable(${PROJECT_NAME} object.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

message("Build type:" ${CMAKE_BUILD_TYPE})
message("C FLAGS DEBUG:" ${CMAKE_C_FLAGS_DEBUG})
message("C FLAGS RELEASE:" ${CMAKE_C_FLAGS_RELEASE})
message("INSTALL PREFIX:" ${CMAKE_INSTALL_PREFIX})
