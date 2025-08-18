#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char* target) {
    regex_t regex;
    int reti;

    // Compile the regular expression for matching "example.com"
    reti = regcomp(&regex, ".*example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Check if the target matches the regular expression
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    redirect(argv[1]);

    return EXIT_SUCCESS;
}