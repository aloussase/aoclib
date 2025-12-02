add_executable(aoc202501 main.c)
target_compile_options(aoc202501 PRIVATE -Wall -Wextra)
target_link_libraries(aoc202501 PUBLIC aoc)