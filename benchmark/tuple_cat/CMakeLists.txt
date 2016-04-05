# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.my_tuple_cat my_tuple_cat.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.std_tuple_cat std_tuple_cat.cpp.erb "(0..100).step(10)")
metabench_add_benchmark(benchmark.tuple_cat
    DATASETS dataset.my_tuple_cat
             dataset.std_tuple_cat
    CHART chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/index
)
