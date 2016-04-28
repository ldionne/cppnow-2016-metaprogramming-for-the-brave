# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include(metabench)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../code)


# logical_and/light
metabench_add_dataset(dataset.logical_and.light.eager     logical_and/light/eager.cpp.erb     "(0..2000).step(50)")
metabench_add_dataset(dataset.logical_and.light.lazy      logical_and/light/lazy.cpp.erb      "(0..2000).step(50)")
metabench_add_dataset(dataset.logical_and.light.recursive logical_and/light/recursive.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.logical_and.light
    DATASETS dataset.logical_and.light.eager
             dataset.logical_and.light.lazy
             dataset.logical_and.light.recursive
    TITLE "Logical and (light predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/logical_and/light.html
)

# logical_and/heavy
metabench_add_dataset(dataset.logical_and.heavy.eager     logical_and/heavy/eager.cpp.erb     "(0..2000).step(50)")
metabench_add_dataset(dataset.logical_and.heavy.lazy      logical_and/heavy/lazy.cpp.erb      "(0..2000).step(50)")
metabench_add_dataset(dataset.logical_and.heavy.recursive logical_and/heavy/recursive.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.logical_and.heavy
    DATASETS dataset.logical_and.heavy.eager
             dataset.logical_and.heavy.lazy
             dataset.logical_and.heavy.recursive
    TITLE "Logical and (heavy predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/logical_and/heavy.html
)

# filter
metabench_add_dataset(dataset.filter.naive filter/naive.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.filter.good  filter/good.cpp.erb  "(0..100).step(10)")
metabench_add_benchmark(benchmark.filter
    DATASETS dataset.filter.naive
             dataset.filter.good
    TITLE "filter"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/filter/index.html

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
    DEPENDS benchmark.logical_and.light
            benchmark.logical_and.heavy
            benchmark.filter
            benchmark.tuple_cat
)
