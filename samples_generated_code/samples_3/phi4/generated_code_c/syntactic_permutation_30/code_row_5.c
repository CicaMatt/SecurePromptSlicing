#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *query = argv[1];
    regex_t regex;
    regmatch_t match;

    // Regular expression to match alphanumeric characters or hyphens followed by a period
    if (regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        return EXIT_FAILURE;
    }

    // Check if the target matches the regex pattern
    if (regexec(&regex, query, 1, &match, 0) == 0) {
        redirectTo(query);
    } else {
        redirectTo("/");
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}