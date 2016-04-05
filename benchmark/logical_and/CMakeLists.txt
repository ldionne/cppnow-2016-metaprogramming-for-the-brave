# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.lazy_logical_and-light light/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.eager_logical_and-light light/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.logical_and-light
    DATASETS dataset.lazy_logical_and-light
             dataset.eager_logical_and-light
    CHART light/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/light/index
)

# The same benchmark as above, but where evaluating the booleans is heavy.
metabench_add_dataset(dataset.lazy_logical_and-heavy heavy/lazy.cpp.erb "(0..2000).step(50)")
metabench_add_dataset(dataset.eager_logical_and-heavy heavy/eager.cpp.erb "(0..2000).step(50)")
metabench_add_benchmark(benchmark.logical_and-heavy
    DATASETS dataset.lazy_logical_and-heavy
             dataset.eager_logical_and-heavy
    CHART heavy/chart.json
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/heavy/index
)
