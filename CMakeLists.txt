cmake_minimum_required(VERSION 4.1)
project(convex_hull)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(convex_hull main.cpp
        App.cpp
        App.h)

target_include_directories(convex_hull PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(convex_hull PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)