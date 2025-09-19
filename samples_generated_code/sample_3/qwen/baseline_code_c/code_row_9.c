#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=some-value"; // Example query string
    const char *param_name = "target";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    char *value_start = strstr(query, param_name);
    if (value_start == NULL) {
        printf("Redirecting to root: /\n");
        return 0;
    }

    value_start += strlen(param_name) + 1; // Move past 'target='
    char *value_end = strchr(value_start, '&');
    size_t value_len = value_end != NULL ? (size_t)(value_end - value_start) : strlen(value_start);

    char target[value_len + 1];
    strncpy(target, value_start, value_len);
    target[value_len] = '\0';

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root: /\n");
    }

    regfree(&regex);
    return 0;
}