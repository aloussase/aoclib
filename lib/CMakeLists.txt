add_library(aoc aoc.c)
target_compile_options(aoc PUBLIC -Wall -Wextra)
target_include_directories(aoc PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.>)
target_link_libraries(aoc curl)