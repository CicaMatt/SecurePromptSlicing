#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=abc123-def.";
    const char *prefix = "target=";
    const char *target;
    regex_t regex;
    int reti;

    if (strncmp(query, prefix, strlen(prefix)) == 0) {
        target = query + strlen(prefix);

        reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
        if (reti) {
            fprintf(stderr, "Could not compile regex\n");
            return 1;
        }

        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Redirect to: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            printf("Target does not match the regular expression\n");
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 1;
        }

        regfree(&regex);
    } else {
        printf("Query does not start with 'target='\n");
    }

    return 0;
}