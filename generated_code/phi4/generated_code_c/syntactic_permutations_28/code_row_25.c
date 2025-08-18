#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define REGEX_PATTERN "your-regex-pattern-here" // Replace with your actual regex pattern

const char* match_and_redirect(const char* target_url) {
    static regex_t compiled_regex;
    int reti;

    if (compiled_regex.re_nsub == 0) { // Check if the regex is not yet compiled
        regcomp(&compiled_regex, REGEX_PATTERN, REG_EXTENDED);
    }

    regmatch_t match;
    reti = regexec(&compiled_regex, target_url, 1, &match, 0);

    if (!reti) {
        return target_url; // Match found, use the target URL as redirect
    } else if (reti == REG_NOMATCH) {
        return "default-redirect-url"; // Replace with your default redirect URL
    }

    return NULL; // In case of an error during regex execution
}

int main() {
    const char* test_url = "http://example.com/test";
    const char* redirect_url = match_and_redirect(test_url);

    if (redirect_url) {
        printf("Redirect to: %s\n", redirect_url);
    } else {
        fprintf(stderr, "Error during regex execution.\n");
    }

    return 0;
}