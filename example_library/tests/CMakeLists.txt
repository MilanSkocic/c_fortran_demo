link_directories(${LIB_DIRS})

add_executable(runtests runtests.c)
target_include_directories(runtests PRIVATE ../include)
target_link_libraries(runtests m example)
