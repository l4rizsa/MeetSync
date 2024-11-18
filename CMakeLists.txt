cmake_minimum_required(VERSION 3.29)
project(MeetSync C)

set(CMAKE_C_STANDARD 11)

add_executable(MeetSync main.c
        reserva.c)
