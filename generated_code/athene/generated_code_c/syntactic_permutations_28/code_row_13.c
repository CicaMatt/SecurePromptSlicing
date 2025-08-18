#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex() {
    const char *pattern = "^https?://[^/]+/redirect/.*$";
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char *get_redirect_target(const char *target) {
    if (regexec(&regex, target, 0, NULL, 0) != 0) {
        return default_url;
    }
    return target;
}

int main() {
    if (compile_regex() != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    const char *test_urls[] = {"http://example.com/redirect/somewhere", "http://invalid.com"};
    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Target URL: %s -> Redirect to: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}