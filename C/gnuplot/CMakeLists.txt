cmake_minimum_required(VERSION 3.10)

project(gnuplot LANGUAGES C)


if(WIN32)
	if(MSVC)
		MESSAGE(STATUS "Compiling with MSVC on Win32")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/win_msvc)
	endif(MSVC)
	if(MSYS)
		MESSAGE(STATUS "Compiling with MSYS on Win32")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/win_msys)
	endif(MSYS)
endif(WIN32)

if(UNIX)
	if(MSYS)
		MESSAGE(STATUS "Compiling with MSYS on UNIX")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_msys)
	else()
		MESSAGE(STATUS "Compiling with GCC on UNIX")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_gcc)
	endif(MSYS)
endif(UNIX)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE gnuplot.c)

