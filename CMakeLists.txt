cmake_minimum_required(VERSION 3.27)
project(CDdataframe C)

set(CMAKE_C_STANDARD 11)

add_executable(CDdataframe main.c
        colonne.c
        colonne.h
        cdataframe.c
        cdataframe.h
        menu.c
        menu.h
)
