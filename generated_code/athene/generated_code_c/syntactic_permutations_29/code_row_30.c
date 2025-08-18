#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define REGEX "example\\.com"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "target") != 0) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("\r\n");
        return 1;
    }

    const char *target = argv[2];
    regex_t regex;
    int reti;

    if (regcomp(&regex, REGEX, REG_EXTENDED | REG_NOSUB) != 0) {
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("\r\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        printf("HTTP/1.1 403 Forbidden\r\n");
        printf("\r\n");
        return 1;
    }

    redirect(target);

    regfree(&regex);
    return 0;
}