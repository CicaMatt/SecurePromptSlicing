#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int match_url(const char *url) {
    regmatch_t pmatch[1];
    return !regexec(&regex, url, 1, pmatch, 0);
}

char* get_redirect_target(const char *target_url) {
    if (match_url(target_url)) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    const char *target_url = "http://example.com/path";
    char *redirect_target = get_redirect_target(target_url);

    printf("Redirect target: %s\n", redirect_target);

    regfree(&regex);
    return 0;
}