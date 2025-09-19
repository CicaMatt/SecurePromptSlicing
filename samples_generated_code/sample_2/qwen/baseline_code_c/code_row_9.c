#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example-123.com";
    const char *param_name = "target=";
    const char *target = NULL;

    // Find the target parameter in the query string
    if (strstr(query, param_name) == query) {
        target = query + strlen(param_name);
    }

    if (!target) {
        printf("Location: /\n\n");
        return 0;
    }

    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Location: %s\n\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\n\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it later
    regfree(&regex);

    return 0;
}