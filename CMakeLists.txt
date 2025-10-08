cmake_minimum_required(VERSION 4.0)
project(convex_hull)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CONVEX_BUILD_GUI "Build the SFML app" ON)

if(DEFINED ENV{GITHUB_ACTIONS})
    set(CONVEX_BUILD_GUI OFF CACHE BOOL "" FORCE)
endif()

add_library(convex_core
        algorithms/IAlgorithm.h
        algorithms/AndrewAlgorithm.h
        algorithms/AndrewAlgorithm.cpp
        algorithms/QuickhullAlgorithm.h
        algorithms/QuickhullAlgorithm.cpp
        point_providers/Point.h
        point_providers/FromFilePointProvider.h
        point_providers/FromFilePointProvider.cpp
        point_providers/RandomPointProvider.h
        point_providers/RandomPointProvider.cpp
)

target_include_directories(convex_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(CONVEX_BUILD_GUI)
    find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

    add_executable(convex_hull
            main.cpp
            visualization/App.cpp
            visualization/App.h
            performance/Performance.cpp
            performance/Performance.h
            assets/DejaVuSans.h
    )

    target_include_directories(convex_hull PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    target_link_libraries(convex_hull PRIVATE
            convex_core
            SFML::Graphics
            SFML::Window
            SFML::System
    )
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)
