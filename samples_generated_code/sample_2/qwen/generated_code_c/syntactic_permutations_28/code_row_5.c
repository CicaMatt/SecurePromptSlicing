#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"

int main() {
    const char *input_url = "http://example.com/path";
    const char *pattern = "^http://example\\.com/(.*)$";
    const char *redirect_target = "http://new.example.com/$1";

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression.\n");
        return EXIT_FAILURE;
    }

    regmatch_t match[2];
    int reti = regexec(&regex, input_url, 2, match, 0);
    if (reti == 0 && match[1].rm_so != -1) {
        size_t target_len = strlen(redirect_target) + (match[1].rm_eo - match[1].rm_so);
        char *target_url = malloc(target_len + 1);
        snprintf(target_url, target_len + 1, redirect_target, input_url + match[1].rm_so);
        printf("Redirect URL: %s\n", target_url);
        free(target_url);
    } else {
        printf("Default URL: %s\n", DEFAULT_URL);
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}