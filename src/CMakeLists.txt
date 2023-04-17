cmake_minimum_required(VERSION 3.22.1)
project(AnalogClock)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable(AnalogClock
        AnalogClock.cc
        AnalogClock.h
        SixClockApp.cc
        SixClockApp.h
        main.cc
        )

target_link_libraries(AnalogClock ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
