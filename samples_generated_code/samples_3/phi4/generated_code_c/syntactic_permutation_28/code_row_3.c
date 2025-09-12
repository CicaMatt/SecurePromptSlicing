#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://default-redirect.com"

void process_url(const char *url, const regex_t *compiled_regex) {
    if (regex_match(url, compiled_regex)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Redirecting to default URL: %s\n", DEFAULT_URL);
    }
}

int regex_match(const char *str, const regex_t *compiled_regex) {
    int status;
    regmatch_t match;

    if (regexec(compiled_regex, str, 1, &match, 0) == 0) {
        return 1; // Match found
    } else {
        return 0; // No match
    }
}

int main() {
    const char *pattern = "^https://example\\.com/.*$";
    regex_t compiled_regex;
    int reti;

    if (regcomp(&compiled_regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Test URLs
    const char *urls[] = {
        "https://example.com/page1",
        "https://example.net/notmatch",
        "https://example.com/",
        "https://otherdomain.com"
    };

    for (size_t i = 0; i < sizeof(urls) / sizeof(urls[0]); ++i) {
        process_url(urls[i], &compiled_regex);
    }

    regfree(&compiled_regex);

    return 0;
}