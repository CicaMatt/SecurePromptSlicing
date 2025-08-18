#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int check_url(const char *url) {
    regex_t regex;
    int reti;

    const char *pattern = ".*example\\.com.*";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    return !reti;
}

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main() {
    char target[MAX_URL_LENGTH];
    const char *query = getenv("QUERY_STRING");

    if (query && sscanf(query, "target=%2047s", target) == 1) {
        if (check_url(target)) {
            redirect(target);
        } else {
            redirect("/");
        }
    } else {
        redirect("/");
    }

    return 0;
}