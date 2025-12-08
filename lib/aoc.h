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

// DS

typedef struct {
   unsigned int id;
   unsigned long int start;
   unsigned long int end;
} AocRange;

typedef struct aocIntervalNode {
   AocRange *range;
   unsigned long int max;
   struct aocIntervalNode *left;
   struct aocIntervalNode *right;
} AocIntervalNode;

void aoc_run(Aoc *aoc, InputMode input_mode);

AocIntervalNode* aoc_interval_tree_insert( AocIntervalNode*root, AocRange *range);
AocRange* aoc_interval_tree_search( AocIntervalNode* root, AocRange range);
int aoc_interval_tree_is_completely_contained( AocIntervalNode* root, AocRange range);
AocIntervalNode* aoc_new_interval_node(AocRange *range);
int aoc_ranges_interval(AocRange r1, AocRange r2);
int aoc_ranges_compare(const void *r1, const void *r2);

// Parsing

/// Read the next integer and return a pointer to the end in the input string.
/// To check that no integer was read:
/// Example: if (aoc_read_int(s, &n) == s)
const char *aoc_read_int(const char* s, int *out);

const char* aoc_read_line(const char*s, char* out);

#endif //AOCLIB_AOC_H