add_executable(aoc202502 main.c)
target_compile_options(aoc202502 PRIVATE -Wall -Wextra)
target_link_libraries(aoc202502 PUBLIC aoc)