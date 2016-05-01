# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.homogeneous.array array.cpp.erb "(0..200).step(10)")
metabench_add_dataset(dataset.homogeneous.tuple tuple.cpp.erb "(0..200).step(10)")

set_property(TARGET dataset.homogeneous.tuple dataset.homogeneous.array
             APPEND PROPERTY COMPILE_OPTIONS -O3)

metabench_add_chart(benchmark.homogeneous
    DATASETS dataset.homogeneous.tuple dataset.homogeneous.array
    TITLE "Execution time as a function of the number of elements"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../homogeneous.html
    ASPECT EXECUTION_TIME
)
