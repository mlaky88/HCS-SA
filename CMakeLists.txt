SET(CMAKE_BUILD_TYPE Release)
project(HCS-SA)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Algorithm SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Individual SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/BenchmarkCEC2014 SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/HybridCuckoo SRC_LIST)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
set(CMAKE_VERBOSE_MAKEFILE "on")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")



