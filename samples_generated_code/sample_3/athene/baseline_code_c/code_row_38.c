#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_regex(const char *target) {
    regex_t regex;
    int reti;
    const char *pattern = ".*example\\.com.*";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void handle_request(const char *target) {
    if (check_regex(target)) {
        printf("Location: %s\r\n", target);
    } else {
        printf("Location: /\r\n");
    }
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) > MAX_URL_LENGTH) {
        handle_request("/");
    } else {
        handle_request(target);
    }
    return 0;
}