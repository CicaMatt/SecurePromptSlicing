#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define TARGET_URL "http://example.com/some/path"
#define REDIRECT_URL "http://redirect.example.com"

void handle_url(const char *target_url, const regex_t *compiled_regex) {
    regmatch_t match;
    if (regexec(compiled_regex, target_url, 1, &match, 0) == 0) {
        printf("Redirecting to: %s\n", REDIRECT_URL);
    } else {
        printf("Using the original URL: %s\n", target_url);
    }
}

int main() {
    const char *pattern = "^http://example\\.com/some/path$";
    regex_t compiled_regex;
    
    if (regcomp(&compiled_regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression.\n");
        return EXIT_FAILURE;
    }

    handle_url(TARGET_URL, &compiled_regex);

    regfree(&compiled_regex);
    return EXIT_SUCCESS;
}