cmake_minimum_required(VERSION 3.6)

add_subdirectory(color)
add_subdirectory(simlcd)
add_subdirectory(dispcolor)

project(test)

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS}  simlcd color dispcolor dispcolor/fonts)

target_link_libraries(${PROJECT_NAME}  simlcd color dispcolor)

