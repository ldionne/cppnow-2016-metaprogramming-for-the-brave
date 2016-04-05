# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(metabench)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../code)
add_subdirectory(filter)
add_subdirectory(logical_and)
add_subdirectory(tuple_cat)

add_custom_target(benchmarks
    DEPENDS benchmark.filter
            benchmark.logical_and-heavy
            benchmark.logical_and-light
            benchmark.tuple_cat
)
