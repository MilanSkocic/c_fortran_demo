cmake_minimum_required(VERSION 3.10)


project(tkgui C)

set(CMAKE_C_STANDARD 99)


set(LIB_MSYS C:/Users/mskocic/LocalApps/Miniconda3/Library/lib/tcl86t.lib C:/Users/mskocic/LocalApps/Miniconda3/Library/lib/tk86t.lib)
set(INC_MSYS C:/Users/mskocic/LocalApps/Miniconda3/Library/include)

set(LIB_UNIX )
set(INC_UNIX /usr/include/tcl)


if(WIN32)
	if(COMPILER STREQUAL "Intel")
		MESSAGE(STATUS "Compiling with Intel on Win32")
		set(CMAKE_C_COMPILER icl)
	endif(COMPILER STREQUAL "Intel")
	if(MSVC)
		MESSAGE(STATUS "Compiling with MSVC on Win32")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/win_msvc)
		set(LIB_DIR ${LIB_MSYS})	
		set(INC_DIR ${INC_MSYS})	
	endif(MSVC)
	if(MSYS)
		MESSAGE(STATUS "Compiling with MSYS on Win32")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/win_msys)
		set(LIB_DIR ${LIB_MSYS})	
		set(INC_DIR ${INC_MSYS})	
	endif(MSYS)
endif(WIN32)

if(UNIX)
	if(COMPILER STREQUAL "Intel")
		MESSAGE(STATUS "Compiling with Intel on Unix")
		set(CMAKE_C_COMPILER icc)
	endif(COMPILER STREQUAL "Intel")
	if(MSYS)
		MESSAGE(STATUS "Compiling with MSYS on UNIX")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_msys)
		set(LIB_DIR ${LIB_MSYS})	
		set(INC_DIR ${INC_MSYS})	
	else()
		MESSAGE(STATUS "Compiling with GCC on UNIX")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unix_gcc)
		set(LIB_DIR ${LIB_UNIX})
		set(INC_DIR ${INC_UNIX})	
	endif(MSYS)
endif(UNIX)

add_executable(tkgui)
target_sources(tkgui PRIVATE tkgui.c)
target_include_directories(tkgui PRIVATE ${INC_DIR})
target_link_directories(tkgui PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(tkgui PRIVATE X11 tk tcl)

#configure_file(${CMAKE_SOURCE_DIR}/test.tcl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test.tcl COPYONLY)
