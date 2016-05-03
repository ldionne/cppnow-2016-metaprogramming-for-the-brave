# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.tuple_cat.hana hana.cpp.erb "(0..70).step(10)" NAME "hana")
metabench_add_dataset(dataset.tuple_cat.std  std.cpp.erb  "(0..70).step(10)" NAME "std")

metabench_add_chart(benchmark.tuple_cat
    DATASETS dataset.tuple_cat.hana dataset.tuple_cat.std
    TITLE "Compilation time of tuple_cat"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/index.html
)

add_dependencies(benchmarks benchmark.tuple_cat)
