#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

void handle_url(const char *url) {
    regex_t regex;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    int result = regexec(&regex, url, 1, &match, 0);

    if (!result) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Redirecting to: %s\n", DEFAULT_URL);
    }

    regfree(&regex);
}

int main() {
    const char *test_urls[] = {
        "http://example.com/page1",
        "https://www.example.com/page2",
        "http://not-example.com",
        "https://example.org"
    };

    size_t num_urls = sizeof(test_urls) / sizeof(test_urls[0]);

    for (size_t i = 0; i < num_urls; ++i) {
        printf("Processing: %s\n", test_urls[i]);
        handle_url(test_urls[i]);
    }

    return 0;
}