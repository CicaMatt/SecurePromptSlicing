#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_regex(const char *target) {
    regex_t regex;
    int reti;
    const char *pattern = ".*example\\.com.*";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

void redirect(const char *target) {
    printf("Location: %s\r\n", target);
    printf("\r\n");
    exit(0);
}

int main() {
    char *query = getenv("QUERY_STRING");
    if (query == NULL) {
        redirect("/");
    }

    char target[MAX_URL_LENGTH] = "";
    sscanf(query, "target=%[^&]", target);

    if (check_regex(target)) {
        redirect(target);
    } else {
        redirect("/");
    }

    return 0;
}