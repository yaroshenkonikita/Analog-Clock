cmake_minimum_required(VERSION 3.22.1)
project(AnalogClock)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
#find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}) #${OPENGL_INCLUDE_DIRS})

#set(CMAKE_PREFIX_PATH " /usr/lib/x86_64-linux-gnu" ${CMAKE_PREFIX_PATH})

#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIRS})

#add_custom_command(TARGET AnalogClock PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:AnalogClock>/fonts)

add_executable(AnalogClock
        AnalogClock.cc
        AnalogClock.h
        SixClockApp.cc
        SixClockApp.h
        main.cc
        )

target_link_libraries(AnalogClock ${SDL2_LIBRARIES}) #${OPENGL_LIBRARIES} ${SDL2_TTF_LIBRARIES})