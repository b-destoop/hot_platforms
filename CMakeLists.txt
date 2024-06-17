cmake_minimum_required(VERSION 3.27)
project(hot_platforms)

set(CMAKE_CXX_STANDARD 23)

# Find the ncurses package
find_package(Curses REQUIRED)

# Include ncurses headers
include_directories(${CURSES_INCLUDE_DIR})

add_executable(hot_platforms main.cpp
        cmake-build-debug/Game.cpp
        cmake-build-debug/Game.h
        IOcontroller/IOController.h
        IOcontroller/PcIOController.cpp
        IOcontroller/PcIOController.h
        BombMode.cpp
        BombMode.h
        settings.cpp
        settings.h
        game.h
)

# Link the ncurses library
target_link_libraries(hot_platforms ${CURSES_LIBRARIES})
