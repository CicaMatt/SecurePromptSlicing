#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: %s\n\n", url);
}

int main() {
    const char *pattern = "(.*example\\.com.*)";
    regex_t regex;
    regmatch_t match;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    const char *input = getenv("QUERY_STRING");

    if (input == NULL || regexec(&regex, input, 1, &match, 0) != 0) {
        redirectTo("/");
    } else {
        char target[256];
        strncpy(target, input + match.rm_so, match.rm_eo - match.rm_so);
        target[match.rm_eo - match.rm_so] = '\0';
        redirectTo(target);
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}


To compile and run this code, you can use:


gcc -o web_redirect web_redirect.c
export QUERY_STRING="http://www.example.com/somepath"
./web_redirect


This program reads the `QUERY_STRING` environment variable as input, which simulates a URL query parameter. It checks if the target matches the regular expression and redirects accordingly.