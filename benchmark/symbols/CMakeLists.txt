# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.symbols.et et.cpp.erb "(0..100_000).step(1000)" ENV "{TREE_HEIGHT: 6}")

metabench_add_dataset(dataset.symbols.et.O3 et.cpp.erb "(0..100_000).step(1000)" ENV "{TREE_HEIGHT: 6}" NAME "with -O3")
set_property(TARGET dataset.symbols.et.O3 APPEND PROPERTY COMPILE_OPTIONS -O3)

metabench_add_dataset(dataset.symbols.et.LTO et.cpp.erb "(0..100_000).step(1000)" ENV "{TREE_HEIGHT: 6}" NAME "with -flto")
set_property(TARGET dataset.symbols.et.LTO APPEND PROPERTY COMPILE_OPTIONS -flto)
set_property(TARGET dataset.symbols.et.LTO APPEND PROPERTY LINK_FLAGS -flto)

metabench_add_benchmark(benchmark.symbols.time
    DATASETS dataset.symbols.et
    TITLE "Compile-time as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/time.html
    ASPECT COMPILATION_TIME
)

metabench_add_benchmark(benchmark.symbols.size
    DATASETS dataset.symbols.et
    TITLE "Executable size as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/size.html
    ASPECT EXECUTABLE_SIZE
)

metabench_add_benchmark(benchmark.symbols.size_compare
    DATASETS dataset.symbols.et.O3 dataset.symbols.et.LTO
    TITLE "Executable size as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/size_compare.html
    ASPECT EXECUTABLE_SIZE
)
