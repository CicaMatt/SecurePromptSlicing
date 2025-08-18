#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc-123.";
    const char *prefix = "target=";
    char *value;
    regex_t re;
    int reti;

    if (strncmp(query, prefix, strlen(prefix)) == 0) {
        value = strdup(query + strlen(prefix));
        const char *pattern = "^[a-zA-Z0-9-]+\\.";
        reti = regcomp(&re, pattern, REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
        reti = regexec(&re, value, 0, NULL, 0);
        if (!reti) {
            printf("Redirecting to %s\n", value);
            // In a real application, you would perform the redirection here
        } else if (reti == REG_NOMATCH) {
            puts("No match");
        } else {
            char msgbuf[100];
            regerror(reti, &re, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }
        regfree(&re);
        free(value);
    } else {
        puts("Query does not start with 'target='");
    }

    return 0;
}