#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example-123.test";
    const char *param_name = "target=";
    const char *redirect_url;
    regex_t regex;
    int reti;

    // Find the start of the target parameter value
    const char *param_start = strstr(query, param_name);
    if (param_start == NULL) {
        redirect_url = "/";
        printf("Location: %s\n\n", redirect_url);
        return 0;
    }

    // Get the value of the target parameter
    const char *value_start = param_start + strlen(param_name);
    size_t value_len = strcspn(value_start, "&");
    char target[value_len + 1];
    strncpy(target, value_start, value_len);
    target[value_len] = '\0';

    // Compile the regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        redirect_url = "/";
        printf("Location: %s\n\n", redirect_url);
        return 1;
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect_url = target;
    } else {
        redirect_url = "/";
    }

    // Free memory and print the HTTP header for redirection
    regfree(&regex);
    printf("Location: %s\n\n", redirect_url);

    return 0;
}