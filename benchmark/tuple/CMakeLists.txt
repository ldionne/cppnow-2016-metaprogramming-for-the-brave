# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

# Add new datasets
metabench_add_dataset(dataset.tuple.aligned_storage      "aligned_storage.cpp.erb"      "(0..500).step(10)" NAME "aligned storage")
metabench_add_dataset(dataset.tuple.multiple_inheritance "multiple_inheritance.cpp.erb" "(0..500).step(10)" NAME "multiple inheritance")

# Add a new chart
metabench_add_chart(benchmark.tuple
    DATASETS dataset.tuple.aligned_storage dataset.tuple.multiple_inheritance
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../tuple.html
)

add_dependencies(benchmarks benchmark.tuple)
