cmake_minimum_required(VERSION 3.0)

project(Project)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Project Main.cpp)

target_link_libraries(Project mingw32)
target_link_libraries(Project ${SDL2_LIBRARIES})
