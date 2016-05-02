# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.filter.naive naive.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.filter.good  good.cpp.erb  "(0..100).step(10)")

metabench_add_chart(benchmark.filter
    DATASETS dataset.filter.naive
             dataset.filter.good
    TITLE "filter"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/index.html
)

add_dependencies(benchmarks benchmark.filter)
