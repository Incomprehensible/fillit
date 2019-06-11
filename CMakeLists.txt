cmake_minimum_required(VERSION 3.14)
project(tryfillit)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tryfillit
        ex
        file
        fill3.c
        fillit.h
        ft_input.c
        ft_twolist.c
        get_next_line.c
        get_next_line.h
        libft.a
        libft.h
        main.c)
