#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define REGEX_PATTERN ".*example\\.com.*"

void send_redirect(const char *target) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main(int argc, char **argv) {
    const char *query = getenv("QUERY_STRING");
    if (query == NULL) {
        return 1;
    }

    char *target = strchr(query, '=');
    if (target == NULL || *(target + 1) == '\0') {
        return 1;
    }
    target++;

    regex_t regex;
    int reti;
    if ((reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED)) != 0) {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        return 1;
    }

    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        send_redirect(target);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("\r\n");
        printf("Invalid target URL.\n");
    }

    regfree(&regex);
    return 0;
}