#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex(const char *pattern) {
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char *match_url(const char *target_url) {
    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    }
    return default_url;
}

int main() {
    const char *pattern = "^https?://example\\.org/.*$";
    if (compile_regex(pattern) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        return 1;
    }

    const char *target_url = "http://example.org/path";
    const char *redirect_url = match_url(target_url);
    printf("Redirecting to: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}