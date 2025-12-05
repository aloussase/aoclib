add_executable(aoc202503 main.c)
target_compile_options(aoc202503 PRIVATE -Wall -Wextra)
target_link_libraries(aoc202503 PUBLIC aoc)