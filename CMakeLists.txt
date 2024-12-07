cmake_minimum_required(VERSION 3.26)
project(reseau_trophic C)

set(CMAKE_C_STANDARD 23)

add_executable(reseau_trophic main.c
        reseau_trophique.c
        reseau_trophique.h)
