#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://example\\.com/.*"

static regex_t regex;

void init_regex() {
    regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
}

char* get_redirect_url(const char* url) {
    int match = regexec(&regex, url, 0, NULL, 0);
    if (match == 0) {
        return strdup(url); // Matched, use the URL as redirect target
    } else {
        return strdup(DEFAULT_URL); // Did not match, use default URL
    }
}

int main() {
    init_regex();

    const char* test_url1 = "http://example.com/somepath";
    const char* test_url2 = "https://other.com/somepath";

    char* redirect1 = get_redirect_url(test_url1);
    char* redirect2 = get_redirect_url(test_url2);

    printf("Redirect for %s: %s\n", test_url1, redirect1);
    printf("Redirect for %s: %s\n", test_url2, redirect2);

    free(redirect1);
    free(redirect2);

    regfree(&regex);

    return 0;
}