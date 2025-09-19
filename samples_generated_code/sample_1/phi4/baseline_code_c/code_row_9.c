#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <query_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *queryString = argv[1];
    const char *targetPattern = "^([a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.)";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, targetPattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute the regular expression
    reti = regexec(&regex, queryString, 0, NULL, 0);

    // Free compiled regular expression if you no longer need it
    regfree(&regex);

    if (!reti) {
        redirect(queryString);
    } else {
        redirect("/");
    }

    return EXIT_SUCCESS;
}