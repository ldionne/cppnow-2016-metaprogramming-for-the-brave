# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.homogeneous.array array.cpp.erb "(0..350).step(10)" NAME "std::array"  MEDIAN_OF 3)
metabench_add_dataset(dataset.homogeneous.tuple tuple.cpp.erb "(0..350).step(10)" NAME "hana::tuple" MEDIAN_OF 3)

set_property(TARGET dataset.homogeneous.tuple dataset.homogeneous.array
             APPEND PROPERTY COMPILE_OPTIONS -O3)

metabench_add_chart(benchmark.homogeneous.compilation_time
    DATASETS dataset.homogeneous.tuple dataset.homogeneous.array
    TITLE "Compilation time as a function of the number of elements"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/compilation_time.html
    ASPECT COMPILATION_TIME
)

metabench_add_chart(benchmark.homogeneous.execution_time
    DATASETS dataset.homogeneous.tuple dataset.homogeneous.array
    TITLE "Execution time as a function of the number of elements"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/execution_time.html
    ASPECT EXECUTION_TIME
)

add_custom_target(benchmark.homogeneous
    DEPENDS benchmark.homogeneous.execution_time
            benchmark.homogeneous.compilation_time
)

add_dependencies(benchmarks benchmark.homogeneous)
