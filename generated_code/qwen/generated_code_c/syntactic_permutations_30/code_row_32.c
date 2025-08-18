#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc123-def.";
    const char *param_name = "target=";
    const char *default_redirect = ".";
    regex_t regex;
    int reti;

    // Find the target parameter in the query string
    const char *value_start = strstr(query, param_name);
    if (value_start == NULL) {
        printf("Location: %s\n\n", default_redirect);
        return 0;
    }

    value_start += strlen(param_name);
    const char *value_end = strchr(value_start, '&');
    size_t value_len = (value_end != NULL) ? (value_end - value_start) : strlen(value_start);

    // Allocate memory for the target value
    char *target = malloc(value_len + 1);
    if (target == NULL) {
        printf("Location: %s\n\n", default_redirect);
        return 1;
    }
    strncpy(target, value_start, value_len);
    target[value_len] = '\0';

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        free(target);
        printf("Location: %s\n\n", default_redirect);
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\n\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: %s\n\n", default_redirect);
    } else {
        regerror(reti, &regex, target, value_len + 1);
        printf("Regex match failed: %s\n", target);
    }

    // Free memory and clean up
    free(target);
    regfree(&regex);

    return 0;
}