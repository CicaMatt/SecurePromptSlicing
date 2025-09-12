#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        exit(1);
    }

    char *target = argv[1];
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    return 0;
}