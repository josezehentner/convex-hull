cmake_minimum_required(VERSION 4.0)
project(convex_hull)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(convex_hull main.cpp
        visualization/App.cpp
        visualization/App.h
        point_providers/Point.h
        point_providers/IPointProvider.h
        point_providers/RandomPointProvider.cpp
        point_providers/RandomPointProvider.h
        point_providers/FromFilePointProvider.cpp
        point_providers/FromFilePointProvider.h
        algorithms/IAlgorithm.h
        algorithms/AndrewAlgorithm.cpp
        algorithms/AndrewAlgorithm.h
        algorithms/QuickhullAlgorithm.h
        algorithms/QuickhullAlgorithm.cpp
        performance/Performance.cpp
        performance/Performance.h
        assets/DejaVuSans.h
)

target_include_directories(convex_hull PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(convex_hull PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)
