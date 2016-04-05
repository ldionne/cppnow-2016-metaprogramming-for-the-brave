# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(metabench)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../code)


# filter
metabench_add_dataset(dataset.filter.naive filter/naive.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.filter.good  filter/good.cpp.erb  "(0..100).step(10)")
metabench_add_benchmark(benchmark.filter
    DATASETS dataset.filter.naive
             dataset.filter.good
    CHART filter/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/filter/index
)

# light_logical_and
metabench_add_dataset(dataset.light_logical_and.lazy light_logical_and/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.light_logical_and.eager light_logical_and/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.light_logical_and
    DATASETS dataset.light_logical_and.lazy
             dataset.light_logical_and.eager
    CHART light_logical_and/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/light_logical_and/index
)

# heavy_logical_and
metabench_add_dataset(dataset.heavy_logical_and.lazy heavy_logical_and/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.heavy_logical_and.eager heavy_logical_and/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.heavy_logical_and
    DATASETS dataset.heavy_logical_and.lazy
             dataset.heavy_logical_and.eager
    CHART heavy_logical_and/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/heavy_logical_and/index
)

# tuple_cat
metabench_add_dataset(dataset.my_tuple_cat tuple_cat/my_tuple_cat.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.std_tuple_cat tuple_cat/std_tuple_cat.cpp.erb "(0..100).step(10)")
metabench_add_benchmark(benchmark.tuple_cat
    DATASETS dataset.my_tuple_cat
             dataset.std_tuple_cat
    CHART tuple_cat/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tuple_cat/index
)

add_custom_target(benchmarks
    DEPENDS benchmark.filter
            benchmark.heavy_logical_and
            benchmark.light_logical_and
            benchmark.tuple_cat
)
