cmake_minimum_required(VERSION 3.10)
project(volk)

set(VOLK_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../vendor/volk)
add_subdirectory(${VOLK_SRC_DIR})
