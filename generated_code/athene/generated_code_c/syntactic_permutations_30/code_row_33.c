#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *target = "http://example.com"; // Default redirect
    if (argc > 1) {
        target = argv[1];
    }

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
        printf("Location: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: http://example.com\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex);
    return 0;
}