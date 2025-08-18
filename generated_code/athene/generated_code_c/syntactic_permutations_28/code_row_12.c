#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REDIRECT_PATTERN "^https?://example\\.com/.*"

static regex_t redirect_regex;

void init_redirect_regex() {
    if (regcomp(&redirect_regex, REDIRECT_PATTERN, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Failed to compile regular expression.\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    if (regexec(&redirect_regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    init_redirect_regex();

    const char *test_urls[] = {"http://example.com/path", "https://other.com/path"};
    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Redirect URL for '%s': %s\n", test_urls[i], get_redirect_url(test_urls[i]));
    }

    return 0;
}