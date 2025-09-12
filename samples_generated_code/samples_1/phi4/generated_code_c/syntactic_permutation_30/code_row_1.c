#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s query_string\n", argv[0]);
        return 1;
    }

    const char *queryString = argv[1];
    regex_t regex;
    regmatch_t match;

    // Regular expression to match one or more alphanumeric characters or a period
    if (regcomp(&regex, "^([a-zA-Z0-9]+|\\.)+", REG_EXTENDED) != 0) {
        printf("Could not compile regular expression.\n");
        return 1;
    }

    char *target = strstr(queryString, "target=");
    
    if (!target || target == queryString) { // Ensure 'target=' is present and not at the start
        redirect("/");
        regfree(&regex);
        return 0;
    }
    
    target += strlen("target=");
    int matchResult = regexec(&regex, target, 1, &match, 0);

    if (matchResult == 0) {
        // If it matches, extract the matched substring and redirect to it
        size_t len = match.rm_eo - match.rm_so;
        char *targetUrl = strndup(target + match.rm_so, len);
        printf("Redirecting to: %s\n", targetUrl);
        free(targetUrl);
    } else {
        // If no match, redirect to root
        printf("Redirecting to: /\n");
    }

    regfree(&regex);
    return 0;
}