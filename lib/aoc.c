#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "aoc.h"

typedef struct {
    char* input;
} CurlCallbackData;

static size_t aoc_curl_callback_write_data(
    void *buffer,
    size_t size,
    size_t nmemb,
    void *callbackData
) {
    CurlCallbackData *cbData = callbackData;
    memcpy(cbData->input, buffer, size * nmemb);
}

/**
 *
 * @param day The day to fetch the input for
 * @param year The year to fetch the input for
 * @param input An output buffer where the input will be stored
 * @return Truthy if the call was successful
 */
int aoc_fetch_input(
    const char* day,
    const char* year,
    char* input
) {
    char *cookie = getenv("AOC_COOKIE");
    if (cookie == NULL) {
        fprintf(stderr, "AOC_COOKIE is not set\n");
        return 0;
    }

    int ret = 0;
    CURL *curl = curl_easy_init();

    CurlCallbackData cb;
    cb.input = input;

    char URL[40] = { 0 };
    snprintf(URL, 40, "https://adventofcode.com/%s/day/%s", year, day);

    char cookieHeader[200] = {0};
    snprintf(cookieHeader, 200, "session=%s", cookie);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookieHeader);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, aoc_curl_callback_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cb);

        CURLcode res = curl_easy_perform(curl);

        if (CURLE_OK == res) {
            ret = 1;
        }

        curl_easy_cleanup(curl);
        return ret;
    }
    return ret;
}

// 32 KB input buffer
static const int INPUT_SIZE = 1024 * 32;
static const char *INPUT[INPUT_SIZE] = {0};

void aoc_run(Aoc *aoc, InputMode input_mode) {
    switch (input_mode) {
        case INPUT_MODE_STDIN:
            char *buffer = INPUT;
            while ((buffer = fgets(buffer, INPUT_SIZE, stdin)) != NULL) {
                buffer = strchr(buffer, '\n') + 1;
            }
            aoc->part_one(INPUT);
            aoc->part_two(INPUT);
            break;
    }
}

// DS

AocIntervalNode* aoc_new_interval_node(AocRange *range) {
    AocIntervalNode* node = malloc(sizeof(AocIntervalNode));
    node->range = range;
    node->max = range->end;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int aoc_ranges_interval(AocRange r1, AocRange r2) {
    if (r1.start <= r2.end && r1.end >= r2.start) {
        return 1;
    }
    return 0;
}

int aoc_ranges_compare(const void *r1, const void *r2) {
    unsigned long int s1 = ((const AocRange*)r1)->start ;
    unsigned long int s2 =  ((const AocRange *)r2)->start;
    if  (s1 < s2) {
        return -1;
    }
     if (s1 > s2) {
         return 1;
     }
     return 0;
}

AocRange* aoc_interval_tree_search(
    AocIntervalNode* root,
    AocRange range) {
    if (root == NULL) return NULL;

    if (aoc_ranges_interval(*root->range, range)) {
        return root->range;
    }

    if (root->left != NULL && root->left->max >= range.start)
        return aoc_interval_tree_search(root->left, range);

    return aoc_interval_tree_search(root->right, range);
}

int aoc_interval_tree_is_completely_contained(
    AocIntervalNode* root,
    AocRange range) {
    if (root == NULL) return 0;

    if (range.start >= root->range->start && range.end <= root->range->end)
        return 1;

    if (root->left != NULL && root->left->max >= range.start)
        return aoc_interval_tree_is_completely_contained(root->left, range);

    return aoc_interval_tree_is_completely_contained(root->right, range);
}

AocIntervalNode* aoc_interval_tree_insert(
    AocIntervalNode*root,
    AocRange *range) {
    if (root == NULL)
        return aoc_new_interval_node(range);

    unsigned long int start = root->range->start;

    if (range->start < start)
        root->left = aoc_interval_tree_insert(root->left, range);
    else
        root->right = aoc_interval_tree_insert(root->right, range);

    if (root->max < range->end)
        root->max = range->end;

    return root;
}

// Parsing

const char *aoc_read_int(const char* s, int *out) {
    char buffer[21] = {0};
    int index = 0;
    while (*s && *s >= '0' && *s <= '9') {
        buffer[index++] = *s++;
        if (index >= 21) {
            fprintf(stderr, "integer too big\n");
            exit(1);
        }
    }
    *out = atoi(buffer);
    return s;
}

const char* aoc_read_line(const char*s, char* out) {
    char *end = strchr(s, '\n') ;
    if (end == NULL) return s;
    while (s != end) {
        *out++ = *s++;
    }
    assert(*s == '\n');
    *out++ = '\n';
    *out = '\0';
    return s + 1;
}