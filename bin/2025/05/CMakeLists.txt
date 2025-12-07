add_executable(aoc202505 main.c)
target_compile_options(aoc202505 PRIVATE -Wall -Wextra)
target_link_libraries(aoc202505 PUBLIC aoc)