# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

# light
metabench_add_dataset(dataset.logical_and.light.eager     light/eager.cpp.erb     "(0..2000).step(50)" NAME "eager")
metabench_add_dataset(dataset.logical_and.light.lazy      light/lazy.cpp.erb      "(0..2000).step(50)" NAME "lazy")
metabench_add_dataset(dataset.logical_and.light.recursive light/recursive.cpp.erb "(0..2000).step(50)" NAME "recursive")

metabench_add_chart(benchmark.logical_and.light
    DATASETS dataset.logical_and.light.eager
             dataset.logical_and.light.lazy
             dataset.logical_and.light.recursive
    TITLE "Logical and (light predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/light.html
)

# heavy
metabench_add_dataset(dataset.logical_and.heavy.eager     heavy/eager.cpp.erb     "(0..2000).step(50)" NAME "eager")
metabench_add_dataset(dataset.logical_and.heavy.lazy      heavy/lazy.cpp.erb      "(0..2000).step(50)" NAME "lazy")
metabench_add_dataset(dataset.logical_and.heavy.recursive heavy/recursive.cpp.erb "(0..2000).step(50)" NAME "recursive")

metabench_add_chart(benchmark.logical_and.heavy
    DATASETS dataset.logical_and.heavy.eager
             dataset.logical_and.heavy.lazy
             dataset.logical_and.heavy.recursive
    TITLE "Logical and (heavy predicate)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/heavy.html
)


add_custom_target(benchmark.logical_and
    DEPENDS benchmark.logical_and.heavy
            benchmark.logical_and.light
)

add_dependencies(benchmarks benchmark.logical_and)
