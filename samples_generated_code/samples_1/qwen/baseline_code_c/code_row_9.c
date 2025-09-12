#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query_string = "target=example-123.com";
    const char *param_name = "target=";
    const char *redirect_root = "http://example.com/";
    const char *pattern = "^[-a-zA-Z0-9]+\\.";
    regex_t regex;
    int reti;

    // Find the target parameter in the query string
    char *start = strstr(query_string, param_name);
    if (!start) {
        printf("Location: %s\n\n", redirect_root);
        return 0;
    }

    start += strlen(param_name);
    char *end = strchr(start, '&');
    size_t target_len = end ? (size_t)(end - start) : strlen(start);

    // Allocate memory for the target value
    char *target = malloc(target_len + 1);
    if (!target) {
        printf("Location: %s\n\n", redirect_root);
        return 0;
    }
    strncpy(target, start, target_len);
    target[target_len] = '\0';

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        free(target);
        printf("Location: %s\n\n", redirect_root);
        return 0;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Free allocated memory
    free(target);
    regfree(&regex);

    // Redirect based on regex match
    if (!reti) {
        printf("Location: http://%s\n\n", start);
    } else {
        printf("Location: %s\n\n", redirect_root);
    }

    return 0;
}