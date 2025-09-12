#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int match_example_com(const char *target) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "example\\.com";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);
    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }
}

void handle_request(const char *target) {
    if (match_example_com(target)) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    char target[MAX_URL_LENGTH];
    if (getenv("QUERY_STRING")) {
        sscanf(getenv("QUERY_STRING"), "target=%256s", target);
    } else {
        strcpy(target, "/");
    }

    handle_request(target);

    return 0;
}