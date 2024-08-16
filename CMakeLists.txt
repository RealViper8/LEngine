cmake_minimum_required(VERSION 3.10)

project(EngineLua)

include_directories(include)

add_compile_options(-Wall -Wextra -g -llua -lSDL2)

file(GLOB ENGINE_SRC "src/*.cpp" "src/*.c")

add_executable(el ${ENGINE_SRC})

# api link
link_directories(engine/api/build)
target_link_libraries(el lengine)

# Lua
target_include_directories(el PRIVATE lua/src)
target_link_libraries(el ${PROJECT_SOURCE_DIR}/lua/src/liblua.a)
target_link_libraries(el SDL2main SDL2)
target_link_libraries(el lengine)
