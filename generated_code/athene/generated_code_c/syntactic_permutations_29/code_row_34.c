#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void handle_request(const char *target) {
    const char *pattern = "^[a-zA-Z0-9/.-]+$";

    if (match_regex(target, pattern)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", target);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /\r\n");
        printf("\r\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    const char *target = argv[1];
    if (strlen(target) > MAX_URL_LENGTH) {
        fprintf(stderr, "Target URL is too long.\n");
        return 1;
    }

    handle_request(target);
    return 0;
}