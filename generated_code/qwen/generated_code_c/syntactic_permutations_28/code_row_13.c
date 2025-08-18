#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default-url.com"

void compile_regex(regex_t *regex, const char *pattern) {
    int reti = regcomp(regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

int match_url(const regex_t *regex, const char *url) {
    return !regexec(regex, url, 0, NULL, 0);
}

const char* get_redirect_url(const regex_t *regex, const char *target_url) {
    if (match_url(regex, target_url)) {
        return target_url;
    }
    return DEFAULT_URL;
}

int main() {
    regex_t regex;
    compile_regex(&regex, "^https?://example\\.com/.*");

    const char *target_url = "http://example.com/some/path";
    const char *redirect_url = get_redirect_url(&regex, target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}