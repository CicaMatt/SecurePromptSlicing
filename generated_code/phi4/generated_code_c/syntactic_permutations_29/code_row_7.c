#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect(const char *target) {
    regex_t regex;
    int reti;
    const char *pattern = ".*example\\.com.*";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\r\n", target);
    } else {
        printf("Location: /\r\n");
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    printf("HTTP/1.1 302 Found\r\n");
    redirect(target);
    printf("\r\n");

    return 0;
}