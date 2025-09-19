#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

int main(int argc, char *argv[]) {
    const char *query = "target=example-123.com";
    const char *param_name = "target=";
    char target[MAX_URL_LENGTH] = "";
    regex_t regex;
    int reti;

    // Find the value of the target query parameter
    const char *param_start = strstr(query, param_name);
    if (param_start != NULL) {
        strcpy(target, param_start + strlen(param_name));
        // Cut off at the first '&' to handle multiple parameters
        char *param_end = strchr(target, '&');
        if (param_end != NULL) {
            *param_end = '\0';
        }
    }

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);

    // Check result and redirect accordingly
    if (!reti) {
        printf("Redirecting to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root of the site\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you will no longer use it.
    regfree(&regex);

    return 0;
}