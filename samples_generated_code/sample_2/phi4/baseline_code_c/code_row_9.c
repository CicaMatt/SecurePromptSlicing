#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 2048

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real application, you would use an appropriate method to perform the redirection.
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    const char *regex_pattern = "^[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*\\.$";

    regex_t regex;
    if (regcomp(&regex, regex_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        return EXIT_FAILURE;
    }

    int match = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        redirect(target);
    } else {
        redirect("/");
    }

    return EXIT_SUCCESS;
}