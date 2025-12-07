#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <aoc.h>

typedef int IngredientID;

/**
 * Parse the ranges in the input and return a pointer to the beginning of ingredient IDs.
 * @param input
 * @param ranges
 * @return
 */
const char *parse_ranges(const char* input, AocRange* ranges, int *nranges) {
    unsigned long int start;
    unsigned long int end;

    int id_counter = 0;

    while (sscanf(input, "%ld-%ld\n", &start, &end) == 2) {
        *ranges++ = (AocRange){id_counter++, start, end};
        *nranges += 1;
        input = strchr(input, '\n');
        if (input != NULL)
            input++;
    }

    assert(*input == '\n');
    input++;

    return input;
}

void part_one(const char* input) {
    AocRange ranges[200];
    int nranges = 0;

    const char* ids = parse_ranges(input, ranges, &nranges);
    unsigned long int id;

    int fresh = 0;

    while (sscanf(ids, "%ld\n", &id) == 1) {
        for (int i = 0; i < nranges; i++) {
            if (ranges[i].start <= id && id <= ranges[i].end) {
                fresh += 1;
                break;
            }
        }

        ids = strchr(ids, '\n');
        if (ids != NULL)
            ids++;
    }

    printf("%d\n", fresh);
}

void part_two(const char* input) {
    AocRange ranges[200];
    int nranges = 0;
    parse_ranges(input, ranges, &nranges);

    qsort(ranges, nranges, sizeof(AocRange), aoc_ranges_compare);

    AocRange new_ranges[200];
    int new_ranges_count = 0;

    for (int i = 0; i < nranges; i++) {
        AocRange range = ranges[i];
        int needs_adding = 1;
        for (int j = 0; j < new_ranges_count; j++) {
            if (aoc_ranges_interval(range, new_ranges[j])) {
                AocRange r;
                r.id = j;
                r.start = range.start < new_ranges[j].start ? range.start : new_ranges[j].start;
                r.end = range.end > new_ranges[j].end ? range.end : new_ranges[j].end;
                new_ranges[j] = r;
                needs_adding = 0;
                break;
            }
        }
        if (needs_adding) {
            AocRange r = { .id = new_ranges_count, .start = range.start, .end = range.end };
            new_ranges[new_ranges_count++] = r;
        }
    }

    unsigned long int total = 0;

    for (int i = 0; i < new_ranges_count; i++) {
        total += new_ranges[i].end - new_ranges[i].start + 1;
    }

    printf("%ld\n", total);
}

int main() {
    // const char* sample_input = "3-5\n10-14\n16-20\n12-18\n\n1\n5\n8\n11\n17\n32\n";
    // part_two(sample_input);
    Aoc aoc = { .part_one =  part_one, .part_two = part_two };
    aoc_run(&aoc, INPUT_MODE_STDIN);
}