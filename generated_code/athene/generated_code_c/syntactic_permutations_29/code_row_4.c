#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

int match_regex(const char *target, const char *pattern) {
    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) return 0;

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);
    return !reti;
}

void redirect(const char *target) {
    printf("Location: %s\r\n", target);
    printf("Content-Type: text/html\r\n\r\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strlen(query) == 0) {
        redirect("/");
    }

    char *target = strstr(query, "target=");
    if (target == NULL) {
        redirect("/");
    }

    target += 7; // Skip "target="

    const char *pattern = ".*example\\.com.*";
    if (match_regex(target, pattern)) {
        redirect(target);
    } else {
        redirect("/");
    }
}