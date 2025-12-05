#include <aoc.h>
#include <stdio.h>
#include <string.h>

void part_one(const char* input) {
    long int start;
    long int end;

    long int total = 0;

    while (1) {
        int nread = sscanf(input, "%ld-%ld", &start, &end);
        if (nread != 2) {
            break;
        }

        while (start <= end) {
            long int current = start;

            static char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            snprintf(buffer, sizeof(buffer), "%ld", current);

            size_t len = strlen(buffer);
            if (len % 2 == 0 && strncmp(buffer + len / 2, buffer, len / 2) == 0) {
                total += current;
            }

            start += 1;
        }

        input = strchr(input, ',');
        if (input != NULL) {
            input = input + 1;
        } else {
            break;
        }
    }

    printf("%ld\n", total);
}

void part_two(const char* input) {
    long int start;
    long int end;

    long int total = 0;

    while (1) {
        int nread = sscanf(input, "%ld-%ld", &start, &end);
        if (nread != 2) {
            break;
        }

        while (start <= end) {
            long int current = start;

            static char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            snprintf(buffer, sizeof(buffer), "%ld", current);

            size_t len = strlen(buffer);

            for (int step = len / 2; step > 0; step--) {
                int is_equal = 1;
                for (int i = 1; i * step < len ; i++) {
                    if (memcmp(buffer, buffer + step * i, step) != 0) {
                        is_equal = 0;
                    }
                }
                if (is_equal) {
                    total += current;
                    break;
                }
            }

            start += 1;
        }

        input = strchr(input, ',');
        if (input != NULL) {
            input = input + 1;
        } else {
            break;
        }
    }

    printf("%ld\n", total);
}

int main() {
    const char * sample_input = "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124";
    const char* input = "18623-26004,226779-293422,65855-88510,868-1423,248115026-248337139,903911-926580,97-121,67636417-67796062,24-47,6968-10197,193-242,3769-5052,5140337-5233474,2894097247-2894150301,979582-1016336,502-646,9132195-9191022,266-378,58-91,736828-868857,622792-694076,6767592127-6767717303,2920-3656,8811329-8931031,107384-147042,941220-969217,3-17,360063-562672,7979763615-7979843972,1890-2660,23170346-23308802";
    Aoc aoc = { .part_one =  part_one, .part_two =  part_two };
    part_two(input);
    // aoc_run(&aoc, INPUT_MODE_STDIN);
    return 0;
}