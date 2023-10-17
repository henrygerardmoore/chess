cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(chess LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
  backward
  GIT_REPOSITORY https://github.com/bombela/backward-cpp
  GIT_TAG v1.6)
FetchContent_MakeAvailable(backward)

enable_testing()

find_package(spdlog REQUIRED)
find_package(SFML REQUIRED)
find_package(nlohmann_json REQUIRED)

add_definitions(-g)
add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)

add_executable(chess src/main.cpp src/board.cpp src/game_state_handler.cpp)
add_backward(chess)

target_link_libraries(chess PRIVATE nlohmann_json::nlohmann_json sfml-graphics
                                    spdlog::spdlog)
target_include_directories(chess PRIVATE include)