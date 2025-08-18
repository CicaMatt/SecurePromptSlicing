#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example-123.com";
    const char *prefix = "target=";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    if (strncmp(query, prefix, strlen(prefix)) == 0) {
        const char *target = query + strlen(prefix);
        reti = regcomp(&regex, pattern, REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Redirect to: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            printf("Target does not match the pattern\n");
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 1;
        }

        regfree(&regex);
    } else {
        printf("Query parameter not found\n");
    }

    return 0;
}