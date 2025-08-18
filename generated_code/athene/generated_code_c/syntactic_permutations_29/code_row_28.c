#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Invalid request\n");
        return 1;
    }

    const char *target = strchr(query, '=') + 1;
    if (strchr(target, '&')) {
        *strchr(target, '&') = '\0';
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, ".*example\\.com.*", REG_EXTENDED);
    if (reti) {
        printf("Status: 500 Internal Server Error\n");
        printf("Content-Type: text/plain\n\n");
        printf("Regex compilation failed\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == REG_NOMATCH) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Invalid target URL\n");
        return 1;
    }

    redirect(target);

    return 0;
}