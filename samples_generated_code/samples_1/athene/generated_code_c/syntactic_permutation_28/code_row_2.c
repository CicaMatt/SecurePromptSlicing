#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex(const char *pattern) {
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char *match_url(const char *url) {
    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        return url;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.org/.*$";
    if (compile_regex(pattern) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    const char *test_urls[] = {
        "http://example.org/path",
        "https://example.com/path",
        "http://example.org/"
    };

    for (int i = 0; i < 3; i++) {
        printf("URL: %s -> Redirect to: %s\n", test_urls[i], match_url(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}