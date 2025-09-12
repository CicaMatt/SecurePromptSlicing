#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) return 0;

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void redirect(const char *location) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", location);
    printf("Content-Length: 0\r\n");
    printf("\r\n");
}

int main() {
    char *target = getenv("QUERY_STRING");
    char buffer[BUFFER_SIZE];
    const char *pattern = ".*example\\.com.*";

    if (target == NULL) {
        target = "";
    }

    if (match_regex(target, pattern)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}