cmake_minimum_required(VERSION 3.6)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        challenge.c
        challenge.h
        challenge_room_system_fields.h
        challenge_system.c
        challenge_system.h
        constants.h
        visitor_room.c
        visitor_room.h)

add_executable(HW2 ${SOURCE_FILES})