cmake_minimum_required(VERSION 3.10)
project(progcmake VERSION 1.0 LANGUAGES C)

if(UNIX)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_gcc)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_gcc)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_gcc)
	set(LIB_DIRS ${CMAKE_BINARY_DIR}/unix_gcc)
endif(UNIX)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

enable_testing()
add_test(NAME runtests COMMAND runtests) 


install(TARGETS static_example PUBLIC_HEADER DESTINATION include ARCHIVE DESTINATION lib)
