#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex() {
    const char *pattern = "^https?://[^/]+/(.*)$";
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char* get_redirect_target(const char *target_url) {
    if (regexec(&regex, target_url, 0, NULL, 0) != 0) {
        return default_url;
    }
    return target_url;
}

int main() {
    if (compile_regex() != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        return 1;
    }

    const char *test_urls[] = {"http://example.com/path", "ftp://example.com"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect target for '%s': %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}