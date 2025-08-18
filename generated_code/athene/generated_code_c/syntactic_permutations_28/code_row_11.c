#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex(const char *pattern) {
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }
}

const char *get_redirect_url(const char *target_url) {
    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.com/.*";
    init_regex(pattern);

    const char *target_url = "http://example.com/path";
    const char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    target_url = "http://other.com/path";
    redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}