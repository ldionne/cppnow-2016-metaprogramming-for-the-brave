# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(metabench)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../code)

add_custom_target(benchmarks)

add_subdirectory(homogeneous)
add_subdirectory(logical_and)
add_subdirectory(make_tuple)
add_subdirectory(overloading)
add_subdirectory(remove_if)
add_subdirectory(symbols)
add_subdirectory(tuple_cat)
