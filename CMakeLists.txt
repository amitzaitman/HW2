cmake_minimum_required(VERSION 3.6)
project(HW2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic-errors -Werror")
set(SOURCE_FILES
        challenge.c
        challenge.h
        challenge_room_system_fields.h
        challenge_system.c
        challenge_system.h
        constants.h
        visitor_room.c
        visitor_room.h
        system_additional_types.h
        challenge_system_test_1.c
        test_1.txt)

add_executable(HW2 ${SOURCE_FILES})