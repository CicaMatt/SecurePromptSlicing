#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    char *target = getenv("QUERY_STRING");
    if (target != NULL) {
        regex_t regex;
        int reti;
        char msgbuf[100];

        reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Match found: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            printf("No match\n");
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 1;
        }

        regfree(&regex);
    } else {
        printf("No target query parameter found\n");
    }
    return 0;
}