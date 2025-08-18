#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) return 0;

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void handle_request(const char *target) {
    const char *pattern = ".*example\\.com.*";

    if (match_regex(target, pattern)) {
        redirect(target);
    } else {
        redirect("/");
    }
}

int main() {
    char target[MAX_URL_LENGTH] = "/"; // Default to /
    
    if (getenv("QUERY_STRING")) {
        sscanf(getenv("QUERY_STRING"), "target=%1023s", target);
    }

    printf("Content-Type: text/html\n");
    handle_request(target);

    return 0;
}