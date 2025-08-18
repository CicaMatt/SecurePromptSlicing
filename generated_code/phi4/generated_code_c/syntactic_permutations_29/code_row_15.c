#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    const char *pattern = ".*example\\.com.*";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    redirect(argv[1]);

    printf("Content-Type: text/html\n\n");
    printf("<html><body>Redirecting...</body></html>");

    return 0;
}