# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

# horizontal
metabench_add_dataset(dataset.overloading.horizontal.overloading    horizontal/overloading.cpp.erb    "(0..2000).step(50)" NAME "overloading")
metabench_add_dataset(dataset.overloading.horizontal.specialization horizontal/specialization.cpp.erb "(0..2000).step(50)" NAME "specialization")

metabench_add_chart(benchmark.overloading.horizontal
    DATASETS dataset.overloading.horizontal.overloading
             dataset.overloading.horizontal.specialization
    TITLE "Overload resolution vs specialization (horizontal)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/horizontal.html
)

# vertical
metabench_add_dataset(dataset.overloading.vertical.overloading    vertical/overloading.cpp.erb    "(0..2000).step(50)" NAME "overloading")
metabench_add_dataset(dataset.overloading.vertical.specialization vertical/specialization.cpp.erb "(0..2000).step(50)" NAME "specialization")

metabench_add_chart(benchmark.overloading.vertical
    DATASETS dataset.overloading.vertical.overloading
             dataset.overloading.vertical.specialization
    TITLE "Overload resolution vs specialization (vertical)"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/vertical.html
)


add_custom_target(benchmark.overloading
    DEPENDS benchmark.overloading.vertical
            benchmark.overloading.horizontal
)

add_dependencies(benchmarks benchmark.overloading)
