#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) return 0;

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

void handle_request(const char *target) {
    const char *pattern = "^https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9._%-]*)*$";
    if (match_regex(target, pattern)) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\n\n");
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) > MAX_URL_LENGTH) {
        handle_request("/");
    } else {
        handle_request(target);
    }
    return 0;
}