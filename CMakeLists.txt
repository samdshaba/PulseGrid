cmake_minimum_required(VERSION 3.10)
project(PulseGrid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(PulseGrid src/main.cpp src/Game.cpp)
target_link_libraries(PulseGrid sfml-graphics sfml-window sfml-system)
