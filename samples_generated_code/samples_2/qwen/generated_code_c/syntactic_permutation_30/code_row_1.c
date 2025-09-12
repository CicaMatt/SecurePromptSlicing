#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc123-def"; // Example query string
    const char *pattern = "^target=[a-zA-Z0-9-]+$";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, query, 0, NULL, 0);
    if (!reti) {
        // Extract the target value
        const char *target_start = strchr(query, '=') + 1;
        printf("Redirecting to: %s\n", target_start);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to root\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex);
    return 0;
}