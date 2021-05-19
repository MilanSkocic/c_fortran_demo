cmake_minimum_required(VERSION 3.10)

# -------------------------------------------------------------------------------------
# set the project name
project(progcmake VERSION 1.0 LANGUAGES C)
# -------------------------------------------------------------------------------------


# -------------------------------------------------------------------------------------
# FLAGS
set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_FLAGS_DEBUG "-Wall -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
# -------------------------------------------------------------------------------------


# -------------------------------------------------------------------------------------
# folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/release)


# -------------------------------------------------------------------------------------
# add the target/executable
add_executable(${PROJECT_NAME} main.c 
	tokenobject.c 
	lexerobject.c 
	parserobject.c
	astobject.c
	eis.c)

# target properties
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".out")

target_link_libraries(${PROJECT_NAME} m)

# configuration header
configure_file(version.h.in version.h)

# directories
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
# -------------------------------------------------------------------------------------


