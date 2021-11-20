add_library(test_support STATIC test_support.c)
target_include_directories(test_support PUBLIC .)
target_compile_options(test_support PRIVATE ${OPTIONS})
