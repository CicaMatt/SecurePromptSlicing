#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\r\n\r\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\r\n\r\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);

    return 0;
}