#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        exit(1);
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+", REG_EXTENDED);
    if (reti) {
        printf("Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root: /\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
    }

    regfree(&regex);

    return 0;
}