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
    const char *target = argv[2];

    // Extract the value of the target query parameter
    const char *target_param = "target=";
    char *value_start = strstr(query_string, target_param);
    if (value_start == NULL) {
        printf("Redirecting to root: /\n");
        return 0;
    }

    value_start += strlen(target_param);
    char *value_end = strchr(value_start, '&');
    size_t value_length = value_end ? (size_t)(value_end - value_start) : strlen(value_start);

    char *target_value = malloc(value_length + 1);
    if (!target_value) {
        perror("malloc");
        return 1;
    }
    strncpy(target_value, value_start, value_length);
    target_value[value_length] = '\0';

    // Regular expression to match the pattern
    regex_t regex;
    int reti = regcomp(&regex, "^[a-zA-Z0-9-]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        free(target_value);
        return 1;
    }

    // Match the target value against the regular expression
    reti = regexec(&regex, target_value, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to root: /\n");
    }

    free(target_value);
    return 0;
}