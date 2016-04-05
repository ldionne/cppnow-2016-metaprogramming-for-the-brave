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
    TITLE "filter"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/filter/index.html

)

# light_logical_and
metabench_add_dataset(dataset.light_logical_and.lazy light_logical_and/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.light_logical_and.eager light_logical_and/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.light_logical_and
    DATASETS dataset.light_logical_and.lazy
             dataset.light_logical_and.eager
    TITLE "Logical and (light predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/light_logical_and/index.html
)

# heavy_logical_and
metabench_add_dataset(dataset.heavy_logical_and.lazy heavy_logical_and/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.heavy_logical_and.eager heavy_logical_and/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.heavy_logical_and
    DATASETS dataset.heavy_logical_and.lazy
             dataset.heavy_logical_and.eager
    TITLE "Logical and (heavy predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/heavy_logical_and/index.html
)

# tuple_cat
metabench_add_dataset(dataset.my_tuple_cat tuple_cat/my_tuple_cat.cpp.erb "(0..70).step(10)")
metabench_add_dataset(dataset.std_tuple_cat tuple_cat/std_tuple_cat.cpp.erb "(0..70).step(10)")
metabench_add_benchmark(benchmark.tuple_cat
    DATASETS dataset.my_tuple_cat
             dataset.std_tuple_cat
    TITLE "tuple_cat"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/tuple_cat/index.html
)

add_custom_target(benchmarks
    DEPENDS benchmark.filter
            benchmark.heavy_logical_and
            benchmark.light_logical_and
            benchmark.tuple_cat
)
