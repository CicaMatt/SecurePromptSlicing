#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main() {
    const char *query = "target=example.com";
    const char *param_name = "target=";
    const char *default_redirect = "/";
    char target[MAX_URL_LENGTH] = "";
    regex_t regex;
    int reti;

    // Find the start of the target parameter value
    const char *start = strstr(query, param_name);
    if (start != NULL) {
        start += strlen(param_name);
        size_t len = strcspn(start, "&");
        strncpy(target, start, len);
        target[len] = '\0';
    }

    // Compile the regular expression
    const char *regex_pattern = "^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*$";
    reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    // Redirect based on regex match
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: %s\n", default_redirect);
    }

    return 0;
}