#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex(const char *pattern) {
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char *get_redirect_target(const char *url) {
    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        return url;
    }
    return default_url;
}

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    if (compile_regex(pattern) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    const char *test_urls[] = {"http://example.com/path", "http://other.com"};
    for (int i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); i++) {
        printf("URL: %s, Redirect to: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}