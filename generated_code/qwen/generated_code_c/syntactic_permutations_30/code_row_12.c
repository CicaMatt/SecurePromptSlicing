#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main() {
    const char *query = "target=abc-123"; // Example query string
    const char *param_name = "target=";
    const char *root_url = "http://example.com/";
    regex_t regex;
    int reti;

    // Find the start of the target parameter value
    const char *param_value_start = strstr(query, param_name);
    if (param_value_start == NULL) {
        printf("Redirecting to %s\n", root_url);
        return 0;
    }
    param_value_start += strlen(param_name);

    // Determine the end of the target parameter value
    const char *param_value_end = strchr(param_value_start, '&');
    if (param_value_end == NULL) {
        param_value_end = query + strlen(query);
    }

    // Calculate the length of the target parameter value
    size_t param_value_len = param_value_end - param_value_start;

    // Allocate memory for the target parameter value
    char *target = malloc(param_value_len + 1);
    if (target == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Copy the target parameter value
    strncpy(target, param_value_start, param_value_len);
    target[param_value_len] = '\0';

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        free(target);
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to http://example.com/%s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to %s\n", root_url);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        free(target);
        return 1;
    }

    // Free allocated memory
    regfree(&regex);
    free(target);

    return 0;
}