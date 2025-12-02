#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
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
