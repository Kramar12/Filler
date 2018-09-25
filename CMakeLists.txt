cmake_minimum_required(VERSION 3.12)
project(filler C)

set(CMAKE_C_STANDARD 99)
set(LIBFT ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(filler main.c libft/libft.a filler.h)
target_link_libraries(filler ${LIBFT})