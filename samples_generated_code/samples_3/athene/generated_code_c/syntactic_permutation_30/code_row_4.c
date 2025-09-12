#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
        // Simulate redirection
    } else {
        fprintf(stderr, "Target does not match the regex\n");
    }

    return 0;
}