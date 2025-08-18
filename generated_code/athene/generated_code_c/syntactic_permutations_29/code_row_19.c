#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect(const char *target) {
    printf("Location: %s\n", target);
    printf("\n");
}

int main() {
    char *query = getenv("QUERY_STRING");
    if (query == NULL || strstr(query, "target=") != query) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Missing or invalid target parameter.\n");
        return 1;
    }

    char *target = strchr(query, '=') + 1;
    if (strlen(target) > MAX_URL_LENGTH) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Target parameter too long.\n");
        return 1;
    }

    regex_t regex;
    const char *pattern = "^https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9%_.-]*)*$";
    int reti;

    if ((reti = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
        printf("Status: 500 Internal Server Error\n");
        printf("Content-Type: text/plain\n\n");
        printf("Regex compilation failed.\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (reti != 0) {
        printf("Status: 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Invalid target URL.\n");
        return 1;
    }

    regfree(&regex);

    redirect(target);
    return 0;
}