#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex() {
    int ret;
    const char *pattern = "^https?://example\\.com/.*$";
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    int match;
    match = regexec(&regex, target_url, 0, NULL, 0);
    if (!match) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    init_regex();
    const char *test_urls[] = {"http://example.com/path", "https://other.com"};
    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Redirect URL for '%s' is '%s'\n", test_urls[i], get_redirect_url(test_urls[i]));
    }
    regfree(&regex);
    return 0;
}