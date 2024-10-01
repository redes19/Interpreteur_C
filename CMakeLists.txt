cmake_minimum_required(VERSION 3.27)
project(Interpreteur_C C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(Interpreteur_C
        src/interpreteur.c
        src/interpreteur.h
        src/main.c)