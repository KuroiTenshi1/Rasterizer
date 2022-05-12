cmake_minimum_required(VERSION 3.21)
project(Rasterizer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Rasterizer Common.h Main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Rasterizer sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
