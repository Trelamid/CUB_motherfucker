cmake_minimum_required(VERSION 3.20)
project(CUB C)

set(CMAKE_C_STANDARD 99)

add_executable(CUB
        main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mlx_st/mlx.h
        )

target_link_libraries(CUB
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/libft.a
        ${CMAKE_CURRENT_SOURCE_DIR}/mlx_st/libmlx.a
        "-framework OpenGL"
        "-framework AppKit"
        )
