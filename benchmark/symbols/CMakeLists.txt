# Copyright Louis Dionne 2016
# Distributed under the Boost Software License, Version 1.0.

metabench_add_dataset(dataset.symbols.horizontal horizontal.cpp.erb "(0..100_000).step(1000)")
metabench_add_dataset(dataset.symbols.vertical vertical.cpp.erb "(1..17)")

metabench_add_benchmark(benchmark.symbols.time
    DATASETS dataset.symbols.horizontal dataset.symbols.vertical
    TITLE "Compile-time as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/time.html
    ASPECT COMPILATION_TIME
)

metabench_add_benchmark(benchmark.symbols.size
    DATASETS dataset.symbols.horizontal dataset.symbols.vertical
    TITLE "Executable size as a function of symbol length"
    XLABEL "Symbol length"
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/size.html
    ASPECT EXECUTABLE_SIZE
)
