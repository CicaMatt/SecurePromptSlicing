#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char **argv) {
    const char *target = "/"; // Default target
    if (argc > 1) {
        target = argv[1];
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = ".*example\\.com.*";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\r\n", target);
    } else {
        printf("Location: /\r\n");
    }
    printf("Content-Type: text/html\r\n\r\n");

    regfree(&regex);

    return 0;
}