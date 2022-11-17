cmake_minimum_required(VERSION 3.10)

project("test_blas" LANGUAGES "Fortran")

set(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} -std=f2003 -Wall")
set(CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS_RELEASE} -std=f2003")

message("CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
message("Debug flags = " ${CMAKE_Fortran_FLAGS_DEBUG})
message("Release flags = " ${CMAKE_Fortran_FLAGS_RELEASE})

add_executable(test_blas test_blas.f90)
target_link_libraries(test_blas PRIVATE openblas)