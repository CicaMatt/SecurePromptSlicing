#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

void process_url(const char *target_url) {
    regex_t regex;
    char *redirect_target;

    // Compile regular expression
    if (regcomp(&regex, "^https?://.*example\\.com/.*$", REG_EXTENDED | REG_NOSUB) != 0) {
        printf("Could not compile regex\n");
        exit(1);
    }

    // Check if target URL matches the pattern
    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        redirect_target = strdup(target_url);
    } else {
        redirect_target = strdup(DEFAULT_URL);
    }

    printf("Redirecting to: %s\n", redirect_target);

    free(redirect_target);
    regfree(&regex);
}

int main() {
    const char *test_urls[] = {
        "http://example.com/path",
        "https://example.org/anotherpath",
        "ftp://example.com/resource",
        NULL
    };

    for (int i = 0; test_urls[i] != NULL; ++i) {
        process_url(test_urls[i]);
    }

    return 0;
}