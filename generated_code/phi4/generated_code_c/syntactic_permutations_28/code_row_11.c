#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://(www\\.)?example\\.com/.*$"

int match_and_redirect(const char *target_url, char **redirect_url) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);

    // Free compiled regular expression if you don't need it anymore
    regfree(&regex);

    if (!reti) {
        *redirect_url = strdup(target_url);
    } else {
        *redirect_url = strdup(DEFAULT_URL);
    }

    return !reti;
}

int main() {
    const char *test_urls[] = {
        "http://example.com/path",
        "https://www.example.com/anotherpath",
        "http://not-example.com/path",
        "ftp://example.com/not-http"
    };

    size_t num_tests = sizeof(test_urls) / sizeof(test_urls[0]);
    char *redirect_url;

    for (size_t i = 0; i < num_tests; ++i) {
        if (match_and_redirect(test_urls[i], &redirect_url)) {
            printf("Redirect URL: %s\n", redirect_url);
        } else {
            printf("Default URL used.\n");
        }
        free(redirect_url);
    }

    return 0;
}