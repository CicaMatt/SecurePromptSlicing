#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main(int argc, char *argv[]) {
    const char *target = argv[1];
    regex_t regex;
    int reti;

    if (argc != 2) {
        printf("Location: /\r\n\r\n");
        return 1;
    }

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        printf("Location: /\r\n\r\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\r\n\r\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\r\n\r\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        printf("Regex match failed: %s\n", msgbuf);
        printf("Location: /\r\n\r\n");
    }

    regfree(&regex);
    return 0;
}