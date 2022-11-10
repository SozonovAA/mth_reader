cmake_minimum_required(VERSION 3.14)
project(mth_rd-ex-1 LANGUAGES CXX)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(mth_rd-ex-1)
target_sources(mth_rd-ex-1 PRIVATE ${sources})
