# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.filter.naive filter.naive.cpp.erb "(0..100).step(10)")
metabench_add_dataset(dataset.filter.good  filter.good.cpp.erb  "(0..100).step(10)")
metabench_add_benchmark(benchmark.filter
    DATASETS dataset.filter.naive
             dataset.filter.good
    CHART chart.json
)
