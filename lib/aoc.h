//
// Created by Alexander Goussas on 2/12/25.
//

#ifndef AOCLIB_AOC_H
#define AOCLIB_AOC_H

typedef void AocProblem(const char*);

typedef struct {
   AocProblem *part_one;
   AocProblem *part_two;
} Aoc;

typedef enum {
   INPUT_MODE_STDIN,
} InputMode;

void aoc_run(Aoc *aoc, InputMode input_mode);

#endif //AOCLIB_AOC_H