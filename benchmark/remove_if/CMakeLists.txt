# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.remove_if.recursive recursive.cpp.erb "(1..75).step(5)" NAME "recursive")
metabench_add_dataset(dataset.remove_if.flat      flat.cpp.erb      "(1..75).step(5)" NAME "flat")

metabench_add_chart(benchmark.remove_if.compilation_time
    DATASETS dataset.remove_if.recursive dataset.remove_if.flat
    TITLE "Compilation time as a function of the number of elements"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/compilation_time.html
    ASPECT COMPILATION_TIME
)

metabench_add_chart(benchmark.remove_if.execution_time
    DATASETS dataset.remove_if.recursive dataset.remove_if.flat
    TITLE "Execution time as a function of the number of elements"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/execution_time.html
    ASPECT EXECUTION_TIME
)

add_custom_target(benchmark.remove_if
    DEPENDS benchmark.remove_if.execution_time
            benchmark.remove_if.compilation_time
)

add_dependencies(benchmarks benchmark.remove_if)
