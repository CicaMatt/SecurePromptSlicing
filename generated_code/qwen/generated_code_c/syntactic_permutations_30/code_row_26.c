#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=some-value";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *target = strstr(query, "target=");
    if (target != NULL) {
        target += strlen("target=");
        char *end = strchr(target, '&');
        if (end != NULL) {
            *end = '\0';
        }
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Redirecting to: %s\n", target);
        } else {
            printf("Redirecting to root\n");
        }
    } else {
        printf("Target parameter not found, redirecting to root\n");
    }

    regfree(&regex);
    return 0;
}