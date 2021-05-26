cmake_minimum_required(VERSION 3.10)
project(progcmake VERSION 1.0 LANGUAGES C)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

enable_testing()
add_test(NAME runtests COMMAND runtests) 


install(TARGETS static_example PUBLIC_HEADER DESTINATION include ARCHIVE DESTINATION lib)
