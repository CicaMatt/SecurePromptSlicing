#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query_string = "target=example-123.";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *target = strchr(query_string, '=');
    if (target != NULL) {
        target++; // move pointer to the start of the target value
    } else {
        target = "";
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root\n");
    }

    regfree(&regex);
    return 0;
}