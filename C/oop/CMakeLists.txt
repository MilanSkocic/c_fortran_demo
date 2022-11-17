cmake_minimum_required(VERSION 3.10)

project("object" VERSION "0.1" LANGUAGES C Fortran)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} object.c fib.f90)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE Fortran)

message("Build type:" ${CMAKE_BUILD_TYPE})
message("C FLAGS DEBUG:" ${CMAKE_C_FLAGS_DEBUG})
message("C FLAGS RELEASE:" ${CMAKE_C_FLAGS_RELEASE})
message("Fortan Flags DEBUG:" ${CMAKE_Fortran_FLAGS_DEBUG})
message("Fortan Flags RELEASE:" ${CMAKE_Fortran_FLAGS_RELEASE})
message("INSTALL PREFIX:" ${CMAKE_INSTALL_PREFIX})
