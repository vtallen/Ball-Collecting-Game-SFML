cmake_minimum_required(VERSION 3.14)
project(PickupBalls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES main.cpp game.cpp game.h player.cpp swagball.cpp)
add_executable(PickupBalls ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(PickupBalls sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
