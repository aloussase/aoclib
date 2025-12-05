#include <string.h>
#include <stdio.h>
#include <aoc.h>

static int PART_ONE = 1;

static void get_matrix_dims(const char *input, int *ncols, int *nrows) {
    *ncols = strchr(input, '\n') - input;
    *nrows = 0;
    while (*input) {
        if (*input == '\n') *nrows += 1;
        input++;
    }
}

static int solve(int nrows, int ncols, char M[nrows + 2][ncols + 2]) {
    int total = 0;

    for (int i = 1; i < nrows + 1; i++) {
        for (int j = 1; j < ncols + 1; j++) {
            if (M[i][j] != '@') continue;
            int n = (M[i - 1][j] != '.') + (M[i + 1][j] != '.') +
                    (M[i][j - 1] != '.') + (M[i][j + 1] != '.') +
                    (M[i - 1][j - 1] != '.') + (M[i + 1][j + 1] != '.') +
                    (M[i - 1][j + 1] != '.') + (M[i + 1][j - 1] != '.');
            if (n < 4)
                M[i][j] = PART_ONE ? 'x' : '.';
            total += n < 4;
        }
    }

    return total;
}

static void fill(
    const char *input,
    int nrows,
    int ncols,
    char M[nrows + 2][ncols + 2]) {
    int currow = 1;
    int curcol = 1;

    while (*input) {
        if (*input == '\n') {
            currow += 1;
            curcol = 1;
        } else {
            M[currow][curcol] = *input;
            curcol += 1;
        }
        input++;
    }
}

void part_one(const char *input) {
    int ncols, nrows;
    get_matrix_dims(input, &ncols, &nrows);

    char M[nrows + 2][ncols + 2];
    for (int i = 0; i < nrows +2; i++) {
        for (int j = 0; j < ncols + 2; j++) {
            M[i][j] = '.';
        }
    }

    fill(input, nrows, ncols, M);

    int total = solve(nrows, ncols, M);

    //  for (int i = 0; i < nrows + 2; i++) {
    //      for (int j = 0; j < ncols + 2; j++) {
    //          printf("%c", M[i][j]);
    //      }
    //      printf("\n");
    //  }

    printf("%d\n", total);
}

void part_two(const char *input) {
    int ncols, nrows;
    get_matrix_dims(input, &ncols, &nrows);

    char M[nrows + 2][ncols + 2];
    for (int i = 0; i < nrows +2; i++) {
        for (int j = 0; j < ncols + 2; j++) {
            M[i][j] = '.';
        }
    }

    fill(input, nrows, ncols, M);

    PART_ONE = 0;
    int total = 0;

    while (1) {
        int n = solve(nrows, ncols, M);
        if (n == 0) break;
        total += n;
    }

    printf("%d\n", total);
}

int main() {
    Aoc aoc = {.part_one = part_one, .part_two =   part_two};
    aoc_run(&aoc, INPUT_MODE_STDIN);
}