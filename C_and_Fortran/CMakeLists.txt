cmake_minimum_required(VERSION 3.10)

project(mix_c_f LANGUAGES "C" "Fortran")

add_executable(fmain fmain.f90 c_func.c f_func.f90)
target_link_libraries(fmain openblas)

add_executable(cmain cmain.c c_func.c f_func.f90)