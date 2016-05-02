# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

# sample(main)
include(metabench)

# Add new datasets
metabench_add_dataset(std_tuple  "std.cpp.erb" "(1..50).step(5)")
metabench_add_dataset(hana_tuple "hana.cpp.erb" "(1..50).step(5)")

# Add a new chart
metabench_add_chart(benchmark.make_tuple
    DATASETS std_tuple hana_tuple
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/make_tuple.html
)
# end-sample

add_dependencies(benchmarks benchmark.make_tuple)
