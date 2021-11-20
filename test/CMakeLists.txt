file(GLOB test_sources *test.c)

foreach(file ${test_sources})
    cmake_path(GET file STEM target_name)
    add_executable(${target_name} ${file})
    target_link_libraries(${target_name} PRIVATE incremental_gc test_support)
    target_compile_options(${target_name} PRIVATE ${OPTIONS})
    add_test(${target_name} ${target_name})
endforeach()

add_subdirectory(support)
