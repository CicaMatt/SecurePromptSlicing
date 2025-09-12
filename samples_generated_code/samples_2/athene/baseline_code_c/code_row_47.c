#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_regex(const char *url) {
    regex_t regex;
    const char *pattern = ".*example\\.com.*";
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return reti == 0 ? 1 : 0;
}

void handle_request(const char *target) {
    if (check_regex(target)) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", target);
    } else {
        printf("HTTP/1.1 302 Found\r\nLocation: /\r\n\r\n");
    }
}

int main(int argc, char *argv[]) {
    const char *target = "/";

    if (argc > 1) {
        target = argv[1];
    }

    handle_request(target);

    return 0;
}