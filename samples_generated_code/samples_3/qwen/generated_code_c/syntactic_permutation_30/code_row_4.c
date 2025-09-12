#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

int main() {
    const char *query = "target=example-123.com";
    const char *param_name = "target=";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    char target[MAX_URL_LENGTH] = "";
    regex_t regex;
    int reti;

    // Find the value of the target query parameter
    const char *param_start = strstr(query, param_name);
    if (param_start != NULL) {
        strncpy(target, param_start + strlen(param_name), MAX_URL_LENGTH - 1);
        char *end = strchr(target, '&');
        if (end != NULL) {
            *end = '\0';
        }
    }

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the target variable against the regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Target does not match the required pattern.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free memory used by the regular expression
    regfree(&regex);

    return 0;
}