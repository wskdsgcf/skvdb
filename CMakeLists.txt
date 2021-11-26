cmake_minimum_required(VERSION 3.20)
project(skvdb)

set(CMAKE_CXX_STANDARD 11)

find_path(ROCKSDB_INCLUDE_DIR rocksdb PATHS "")
include_directories(${ROCKSDB_INCLUDE_DIR})
find_library(ROCKSDB_LIB rocksdb)
message(STATUS "finding ${ROCKSDB_LIB}")

add_executable(skvdb main.cpp)
target_link_libraries(skvdb ${ROCKSDB_LIB})
