#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *pattern = "example\\.com";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, argv[1], 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\r\n", argv[1]);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\r\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    printf("\r\n");

    regfree(&regex);

    return 0;
}