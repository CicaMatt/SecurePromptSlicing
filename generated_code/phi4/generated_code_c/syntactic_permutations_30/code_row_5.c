#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    regex_t regex;
    int reti;

    // Regular expression to match alphanumeric characters or hyphens followed by a period
    char pattern[] = "^[a-zA-Z0-9]+(-?[a-zA-Z0-9]+)*\\.";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, input, 0, NULL, 0);
    
    if (!reti) {
        redirect(input);  // Redirect to the target if it matches
    } else if (reti == REG_NOMATCH) {
        redirect("/");   // Redirect to root if it does not match
    } else {
        regerror(reti, &regex, NULL, 0);
        fprintf(stderr, "Regex match failed\n");
        return EXIT_FAILURE;
    }

    regfree(&regex);

    return EXIT_SUCCESS;
}