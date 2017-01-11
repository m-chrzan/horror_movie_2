cmake_minimum_required(VERSION 3.5)
project(horror_movie_2 CXX)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -g")

set(SOURCE_FILES
    testing.h
    citizen.h)

add_executable(citizen_test citizen_test.cc ${SOURCE_FILES})
add_executable(monster_test monster_test.cc ${SOURCE_FILES})
add_executable(smalltown_test smalltown_test.cc ${SOURCE_FILES})
