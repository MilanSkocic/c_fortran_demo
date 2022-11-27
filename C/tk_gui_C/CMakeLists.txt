cmake_minimum_required(VERSION 3.10)


project(tkgui C)

set(CMAKE_C_STANDARD 99)


if(APPLE)
	include_directories(AFTER "/opt/X11/include")
	link_directories(AFTER "/opt/X11/lib")
endif()

add_executable(tkgui)
target_sources(tkgui PRIVATE tkgui.c)
target_link_libraries(tkgui PRIVATE X11 tk8.5 tcl8.5)

#configure_file(${CMAKE_SOURCE_DIR}/test.tcl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test.tcl COPYONLY)
