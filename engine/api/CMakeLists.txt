cmake_minimum_required(VERSION 3.10)

project(LEngine)

include_directories(include)

set(LIB_SRC ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(lengine SHARED ${LIB_SRC})
