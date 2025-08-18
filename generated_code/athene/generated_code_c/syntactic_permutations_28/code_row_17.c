#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex(const char *pattern) {
    regcomp(&regex, pattern, REG_EXTENDED);
}

const char *get_redirect_target(const char *input) {
    if (regexec(&regex, input, 0, NULL, 0) == 0) {
        return input;
    }
    return default_url;
}

int main() {
    const char *pattern = "^https?://example\\.org/.*$";
    init_regex(pattern);

    const char *test_urls[] = {"http://example.org/test", "https://other.com"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect target for '%s': %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}