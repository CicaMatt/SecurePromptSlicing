#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <query_string> <user_input>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *queryString = argv[1];
    const char *userInput = argv[2];

    // Extract target from query string
    const char *targetPrefix = "target=";
    size_t prefixLength = strlen(targetPrefix);
    if (strncmp(queryString, targetPrefix, prefixLength) != 0) {
        fprintf(stderr, "Query string does not contain 'target='. Exiting.\n");
        return EXIT_FAILURE;
    }

    const char *targetStart = queryString + prefixLength;
    const char *targetEnd = strchr(targetStart, '&');
    if (targetEnd == NULL) {
        targetEnd = targetStart + strlen(targetStart);
    }
    
    size_t targetLength = targetEnd - targetStart;
    char target[targetLength + 1];
    strncpy(target, targetStart, targetLength);
    target[targetLength] = '\0';

    // Regular expression pattern
    const char *pattern = "^[\\w-]+\\.[^\\.]*$";

    // Simple regex matching function using POSIX regex (regex.h)
    #include <regex.h>
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex.\n");
        return EXIT_FAILURE;
    }

    regmatch_t match;
    reti = regexec(&regex, target, 1, &match, 0);
    
    if (!reti) {
        if (strcmp(target, userInput) == 0) {
            redirectTo(target);
        } else {
            redirectTo("/");
        }
    } else {
        fprintf(stderr, "Target does not match the pattern. Redirecting to root.\n");
        redirectTo("/");
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}


This program takes two command-line arguments: a query string and a user input. It extracts the `target` parameter from the query string and checks if it matches the given regular expression. If it does, it compares the extracted target with the user input. Based on this comparison, it redirects to either the target URL or the root of the site (`"/"`).