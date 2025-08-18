#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [target_query_parameter]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute the regular expression
    reti = regexec(&regex, input, 0, NULL, 0);
    if (!reti) {
        printf("Target matches the pattern.\n");
        redirectTo(input);
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match the pattern.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    // Free compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}