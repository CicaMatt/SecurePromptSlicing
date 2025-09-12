#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TARGET_LENGTH 256

int main(int argc, char *argv[]) {
    const char *query_param = "target=";
    const char *root_redirect = "http://example.com/";
    char target[MAX_TARGET_LENGTH];
    regex_t regex;
    int reti;

    if (argc < 2) {
        printf("Usage: %s \"query_string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Extract target value from query string
    const char *query_string = argv[1];
    const char *param_value = strstr(query_string, query_param);
    if (param_value == NULL) {
        printf("Location: %s\n", root_redirect);
        printf("\n");
        return EXIT_SUCCESS;
    }

    param_value += strlen(query_param);
    size_t target_length = strcspn(param_value, "& ");
    if (target_length >= MAX_TARGET_LENGTH) {
        printf("Location: %s\n", root_redirect);
        printf("\n");
        return EXIT_SUCCESS;
    }
    strncpy(target, param_value, target_length);
    target[target_length] = '\0';

    // Compile regular expression
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Match target against regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: http://example.com/%s\n", target);
    } else {
        printf("Location: %s\n", root_redirect);
    }
    printf("\n");

    // Free compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}