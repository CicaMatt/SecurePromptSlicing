#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example-page-123.";
    const char *param_name = "target=";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    // Find the start of the target parameter value
    const char *value_start = strstr(query, param_name);
    if (!value_start) {
        printf("Redirecting to root\n");
        return 0;
    }
    value_start += strlen(param_name);

    // Create a copy of the value for regex processing
    char *target_value = strdup(value_start);
    const char *ampersand_pos = strchr(target_value, '&');
    if (ampersand_pos) {
        *ampersand_pos = '\0';
    }

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target_value, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to %s\n", target_value);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free allocated memory
    free(target_value);
    regfree(&regex);

    return 0;
}