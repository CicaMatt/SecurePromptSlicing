#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL) return 1;

    char *target = strstr(query, "target=");
    if (target == NULL) return 1;
    target += strlen("target=");

    regex_t regex;
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret != 0) return 1;

    ret = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        redirect(target);
    } else {
        printf("Status: 400 Bad Request\n");
        printf("\n");
        printf("Invalid target URL.\n");
    }

    return 0;
}