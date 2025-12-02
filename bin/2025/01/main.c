#include <string.h>
#include <stdio.h>
#include <aoc.h>

static int add(int x, int counter, int direction);

void part_one(const char* input) {
    char dir;
    int distance;

    int password = 0;
    int current_count = 50;

    while (1) {
        int nread = sscanf(input, "%c%d\n", &dir, &distance);
        if (nread != 2) {
            break;
        }

        if (dir == 'R') {
            current_count = add(distance, current_count, 1);
        }

        if (dir == 'L') {
            current_count = add(distance, current_count, -1);
        }

        password += current_count == 0 ? 1 : 0;
        input = strchr(input, '\n') + 1;
    }

    printf("%d\n", password);
}

static int add(int x, int counter, int direction) {
    int result = counter;
    int addend = direction < 0 ? -1 : 1;
    while (x > 0) {
        result += addend;
        result = result > 99 ? 0 : result;
        result = result < 0 ? 99 : result;
        x--;
    }
    return result;
}

void part_two(const char* input){}

int main() {
    const char * sample_input = "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82\n";
    Aoc aoc = { .part_one =  part_one, .part_two =  part_two };
    aoc_run(&aoc, INPUT_MODE_STDIN);
    return 0;
}