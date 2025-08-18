#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void redirect_user(char *query_string) {
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    char *target = strstr(query_string, "target=");
    if (target != NULL) {
        target += strlen("target=");
        char *end = strchr(target, '&');
        size_t len = end ? (size_t)(end - target) : strlen(target);
        char buffer[len + 1];
        strncpy(buffer, target, len);
        buffer[len] = '\0';

        reti = regexec(&regex, buffer, 0, NULL, 0);
        if (!reti) {
            printf("Location: %s\n", buffer);
        } else {
            printf("Location: /\n");
        }
    } else {
        printf("Location: /\n");
    }

    printf("\n");
    regfree(&regex);
}

int main() {
    char *query_string = "target=example-123.";
    redirect_user(query_string);

    return 0;
}