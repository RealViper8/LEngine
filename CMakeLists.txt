cmake_minimum_required(VERSION 3.10)

project(EngineLua)

include_directories(include)

add_compile_options(-Wall -Wextra -g)

file(GLOB ENGINE_SRC "src/*.cpp" "src/*.c")

add_executable(el ${ENGINE_SRC})

target_include_directories(el PRIVATE lua/src)
target_link_libraries(el ${PROJECT_SOURCE_DIR}/lua/src/liblua.a)
