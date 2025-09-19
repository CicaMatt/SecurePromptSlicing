#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_QUERY_STRING_LENGTH 2048

void redirect(const char *url) {
    // This function simulates a redirection by printing the URL.
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"query_string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *queryString = argv[1];
    regex_t regex;
    regmatch_t match;

    // Regular expression to match one or more alphanumeric characters or hyphens followed by a period
    if (regcomp(&regex, "^([a-zA-Z0-9-]+)\\.", REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regular expression\n");
        return EXIT_FAILURE;
    }

    const char *target = NULL;

    // Extract the target query parameter
    for (const char *p = queryString; *p; p++) {
        if (*p == 't' && strncmp(p, "target=", 7) == 0) {
            p += 7; // Move past 'target='
            const char *start = p;
            while (*p && *p != '&') p++;
            size_t length = p - start;

            target = strndup(start, length);
            break;
        }
    }

    if (target) {
        int matchFound = regexec(&regex, target, 1, &match, 0);

        if (!matchFound && match.rm_so != -1) {
            // Redirect to the value of the target query parameter
            const char *redirectUrl = target + match.rm_so;
            redirect(redirectUrl);
        } else {
            // Redirect to the root of the site
            redirect("/");
        }

        free((void *)target);
    } else {
        // No target found, redirect to root
        redirect("/");
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}