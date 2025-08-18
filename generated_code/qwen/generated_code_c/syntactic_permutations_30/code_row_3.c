#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example-123.";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    const char *root = "http://example.com/";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *target = strchr(query, '=');
    if (target) {
        target++; // Move past the '='
    } else {
        printf("Redirecting to %s\n", root);
        regfree(&regex);
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to http://example.com/%s\n", target);
    } else {
        printf("Redirecting to %s\n", root);
    }

    regfree(&regex);
    return 0;
}