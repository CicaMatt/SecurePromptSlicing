#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, ".*example\\.com", REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\n\n", target); // Redirect to the target
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\n\n"); // Redirect to /
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_url>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    redirect(argv[1]);

    return 0;
}