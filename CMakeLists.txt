cmake_minimum_required(VERSION 3.22)
project(CHIP_8)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(CHIP_8 main.cpp Chip8.hpp Chip8.cpp Platform.cpp Platform.hpp)

target_include_directories(CHIP_8 PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(CHIP_8 PUBLIC SDL2::SDL2)
target_compile_definitions(CHIP_8 PUBLIC -DSDL_MAIN_HANDLED)