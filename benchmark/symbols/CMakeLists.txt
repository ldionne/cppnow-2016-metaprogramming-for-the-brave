# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.symbols.horizontal horizontal.cpp.erb "(0..100_000).step(1000)" NAME "horizontal")
metabench_add_dataset(dataset.symbols.vertical   vertical.cpp.erb "(1..17)"                   NAME "vertical")

metabench_add_chart(benchmark.symbols.time
    DATASETS dataset.symbols.horizontal dataset.symbols.vertical
    TITLE "Compile-time as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/time.html
    ASPECT COMPILATION_TIME
)

metabench_add_chart(benchmark.symbols.size
    DATASETS dataset.symbols.horizontal dataset.symbols.vertical
    TITLE "Executable size as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/size.html
    ASPECT EXECUTABLE_SIZE
)


metabench_add_dataset(dataset.symbols.hana_bloat.O3   hana_bloat.cpp.erb "(1..500).step(20)" NAME "-O3")
set_property(TARGET dataset.symbols.hana_bloat.O3 APPEND PROPERTY COMPILE_OPTIONS -O3)

metabench_add_dataset(dataset.symbols.hana_bloat.LTO  hana_bloat.cpp.erb "(1..500).step(20)" NAME "-O3 -flto")
set_property(TARGET dataset.symbols.hana_bloat.LTO APPEND PROPERTY COMPILE_OPTIONS -O3 -flto)

metabench_add_chart(benchmark.symbols.hana_bloat.executable_size
    DATASETS dataset.symbols.hana_bloat.O3 dataset.symbols.hana_bloat.LTO
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/hana_bloat_executable_size.html
    ASPECT EXECUTABLE_SIZE
)

metabench_add_chart(benchmark.symbols.hana_bloat.link_time
    DATASETS dataset.symbols.hana_bloat.O3 dataset.symbols.hana_bloat.LTO
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/hana_bloat_link_time.html
    ASPECT LINK_TIME
)


add_custom_target(benchmark.symbols
    DEPENDS benchmark.symbols.time
            benchmark.symbols.size
            benchmark.symbols.hana_bloat.executable_size
            benchmark.symbols.hana_bloat.link_time
)

add_dependencies(benchmarks benchmark.symbols)
