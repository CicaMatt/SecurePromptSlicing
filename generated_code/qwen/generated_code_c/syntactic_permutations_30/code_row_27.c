#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <query_string> <target>\n", argv[0]);
        return 1;
    }

    const char *query_string = argv[1];
    const char *expected_target = argv[2];

    // Regular expression to match the target format
    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Extract target from query string
    const char *query_target = strstr(query_string, "target=");
    if (query_target != NULL) {
        query_target += strlen("target=");
        char *end = strchr((char*)query_target, '&');
        if (end != NULL) {
            *end = '\0';
        }
    } else {
        printf("Redirecting to root: /\n");
        return 0;
    }

    // Check if the extracted target matches the expected format
    reti = regexec(&regex, query_target, 0, NULL, 0);
    if (!reti) {
        if (strcmp(query_target, expected_target) == 0) {
            printf("Redirecting to: %s\n", query_target);
        } else {
            printf("Redirecting to root: /\n");
        }
    } else {
        printf("Target does not match required format. Redirecting to root: /\n");
    }

    regfree(&regex);
    return 0;
}