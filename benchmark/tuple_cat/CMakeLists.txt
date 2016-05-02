# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.my_tuple_cat my_tuple_cat.cpp.erb "(0..70).step(10)")
metabench_add_dataset(dataset.std_tuple_cat std_tuple_cat.cpp.erb "(0..70).step(10)")

metabench_add_chart(benchmark.tuple_cat
    DATASETS dataset.my_tuple_cat
             dataset.std_tuple_cat
    TITLE "tuple_cat"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/index.html
)

add_dependencies(benchmarks benchmark.tuple_cat)
