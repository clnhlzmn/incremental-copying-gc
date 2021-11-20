cmake_minimum_required (VERSION 3.20)
project (incremental_gc)
enable_testing()

add_library(incremental_gc STATIC incremental_gc.c)
target_include_directories(incremental_gc PUBLIC .)
set(OPTIONS "-std=c99" "-Wall" "-Wextra")
target_compile_options(incremental_gc PRIVATE ${OPTIONS})

add_subdirectory(test)
