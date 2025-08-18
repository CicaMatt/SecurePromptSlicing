#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL) {
        printf("Location: http://example.com/\n\n");
        return 0;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        printf("Location: http://example.com/\n\n");
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\n\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: http://example.com/\n\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        printf("Location: http://example.com/\n\n");
    }

    regfree(&regex);
    return 0;
}