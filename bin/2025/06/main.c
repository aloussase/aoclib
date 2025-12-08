#include <aoc.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef enum {
    OP_ADD,
    OP_MUL,
} Op;


static void parse_operations(
    const char*input,
    long double operations[1001][5],
    int *rows,
    int* cols
    ) {
    char line[1024 * 4] = {0};
    const char *input_ptr;

    int i = 0;
    int x = 0;

    while ((input_ptr = aoc_read_line(input, line)) != input) {
        if (*line == '\n') break;

        i = 0;
        int n;
        const char *ptr = line;

        while (*ptr == ' ') ptr++;

        if (*ptr >= '0' && *ptr <= '9') {
            const char *ptr2;
            while ((ptr2 = aoc_read_int(ptr, &n)) != ptr) {
                operations[i++][x] = n;
                if (*ptr2 == '\n') {
                    ptr = ptr2;
                    break;
                }
                assert(*ptr2 == ' ');
                while (*ptr2 && *ptr2 == ' ')
                    ptr2++;
                ptr = ptr2;
            }
        } else {
            while (*ptr != '\n') {
                switch (*ptr) {
                    case '+':
                        operations[i++][x] = OP_ADD;
                        break;
                    case '*':
                        operations[i++][x] = OP_MUL;
                        break;
                    default:
                        assert(0 && "Unhandled operator");
                }
                ptr++;
                while (*ptr == ' ') ptr++;
            }
        }
        assert(*ptr == '\n');
        input = input_ptr;
        x++;
    }

    *rows = x;
    *cols = i;
}

void part_one(const char* input) {
    long double operations[1001][5];
    int nrows, ncols;
    parse_operations(input, operations, &nrows, &ncols);
    printf("rows = %d, cols = %d\n", nrows, ncols);

    for (int j = 0; j < ncols; j++) {
        for (int i = 1; i < nrows - 1; i++) {
            Op op = operations[j][nrows - 1];
            switch (op) {
                case OP_ADD:
                    operations[j][0] += operations[j][i];
                    break;
                case OP_MUL:
                    operations[j][0] *= operations[j][i];
                    break;
            }
        }
    }

    long double total = 0;

    for (int j = 0; j < ncols; j++) {
        total += operations[j][0];
    }

    printf("%Lf\n", total);
}

void part_two(const char* input) {
    // Part II is ridiculous
}

int main() {
    Aoc aoc = {.part_one = part_one, .part_two = part_two};
    aoc_run(&aoc, INPUT_MODE_STDIN);
    return 0;
}