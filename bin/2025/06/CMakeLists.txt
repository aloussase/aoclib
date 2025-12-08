add_executable(aoc202506 main.c)
target_compile_options(aoc202506 PRIVATE -Wall -Wextra)
target_link_libraries(aoc202506 PUBLIC aoc)