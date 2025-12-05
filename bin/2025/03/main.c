#include <aoc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


static void do_(const char *input, size_t N);

void part_one(const char *input) {
    do_(input, 2);
}

void part_two(const char *input) {
    do_(input, 12);
}

static void do_(const char *input, size_t N) {
    char buffer[1024] = {0};
    unsigned long int total = 0;

    while (sscanf(input, "%s\n", buffer) == 1) {
        unsigned long int numbers[N];
        memset(numbers, 0, sizeof(numbers));

        char *bufptr;
        char *lastptr = buffer;
        for (size_t i = 0; i < N; i++) {
            bufptr = lastptr;
            while (strlen(bufptr) >= N - i) {
                int c = *bufptr - '0';
                if (c > numbers[i]) {
                    numbers[i] = c;
                    lastptr = bufptr + 1;
                }
                bufptr++;
            }
        }

        unsigned long int current = 0;
        for (int i = N; i > 0; i--) {
            current += numbers[N - i] * pow(10, i - 1);
        }

        total += current;

        input = strchr(input, '\n');
        if (input != NULL)
            input += 1;
    }
    printf("%ld\n", total);
}

int main() {
    // const char *sample_input = "987654321111111\n811111111111119\n234234234234278\n818181911112111\n";
    // part_two(sample_input);
    Aoc aoc = { .part_one =  part_one, .part_two =  part_two };
    aoc_run(&aoc, INPUT_MODE_STDIN);
}