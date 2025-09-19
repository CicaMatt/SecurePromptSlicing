#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int ret;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return ret == 0;
}

void handle_request(const char *target) {
    if (match_regex(target, REGEX_PATTERN)) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");

    if (target == NULL || strstr(target, "target=") != target) {
        handle_request("/");
    } else {
        target += strlen("target=");
        handle_request(target);
    }

    return 0;
}