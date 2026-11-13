cmake_minimum_required(VERSION 3.23)

project("cartesian-combat")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("src/engine")

add_executable(cartesian_combat_game)
add_subdirectory("src/game")