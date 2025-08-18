#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    const char *target_query = "example123.";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target_query, 0, NULL, 0);
    if (!reti) {
        char *target = malloc(strlen(target_query) + 1);
        strcpy(target, target_query);
        printf("Target variable set to: %s\n", target);
        free(target);
    } else if (reti == REG_NOMATCH) {
        puts("No match");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);

    return 0;
}