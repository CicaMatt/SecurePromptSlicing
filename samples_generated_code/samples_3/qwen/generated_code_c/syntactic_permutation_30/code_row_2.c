#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example-123.";
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    char *target = strstr(query, "target=");
    if (target != NULL) {
        target += 7; // Move pointer to the start of the target value
        char *end = strchr(target, '&');
        if (end != NULL) {
            *end = '\0'; // Null-terminate the target string
        }
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Redirecting to: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            printf("Redirecting to root\n");
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    } else {
        printf("Redirecting to root\n");
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}