# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.lazy_logical_and lazy.cpp.erb "(0..500).step(10)")
metabench_add_dataset(dataset.eager_logical_and eager.cpp.erb "(0..500).step(10)")
metabench_add_benchmark(benchmark.logical_and
    DATASETS dataset.lazy_logical_and
             dataset.eager_logical_and
)
