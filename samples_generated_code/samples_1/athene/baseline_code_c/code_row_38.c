#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define MAX_URL_LENGTH 2048

int match_regex(const char *target) {
    regex_t regex;
    int reti;

    const char *pattern = "example\\.com";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

void redirect(const char *target) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main() {
    char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        redirect("/");
        return 0;
    }

    char target[MAX_URL_LENGTH];
    sscanf(query, "target=%2047s", target);

    if (match_regex(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}