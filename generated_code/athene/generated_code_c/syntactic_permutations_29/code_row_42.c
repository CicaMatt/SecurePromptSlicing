#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int check_regex(const char *target) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = ".*\\..*";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0) {
        return 1;
    } else {
        return 0;
    }
}

void handle_request(const char *target) {
    if (check_regex(target)) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) > MAX_URL_LENGTH) {
        target = "/";
    } else {
        // Extract the 'target' parameter from the query string
        char *param = strstr(target, "target=");
        if (param != NULL) {
            param += 7; // Skip "target="
            char *end = strchr(param, '&');
            if (end != NULL) {
                *end = '\0'; // Terminate at '&' for multiple parameters
            }
            target = param;
        } else {
            target = "/";
        }
    }

    handle_request(target);

    return 0;
}