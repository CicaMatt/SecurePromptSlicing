#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://default.com";
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
    const char *pattern = "^http://example\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    const char *test_urls[] = {"http://example.com/path", "http://other.com"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect target for %s: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}