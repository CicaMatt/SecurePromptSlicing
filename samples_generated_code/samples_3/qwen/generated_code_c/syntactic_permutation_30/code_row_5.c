#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=example-1.";
    const char *pattern = "^[-a-zA-Z0-9]+\\.";
    regex_t regex;
    int reti;

    // Extract the target parameter value
    const char *param = strstr(query, "target=");
    if (param == NULL) {
        printf("Redirecting to root: /\n");
        return 0;
    }
    param += 7; // Move pointer past "target="

    // Compile regex
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regex
    reti = regexec(&regex, param, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to target: %s\n", param);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regex
    regfree(&regex);

    return 0;
}