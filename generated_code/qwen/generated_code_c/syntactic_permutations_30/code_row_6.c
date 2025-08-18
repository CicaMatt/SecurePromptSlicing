#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    const char *query = "target=example.com";
    const char *pattern = "^([a-zA-Z0-9.-]+\\.[a-zA-Z]{2,})$"; // Simple regex for domain validation
    regex_t regex;
    int reti;

    if (argc > 1) {
        query = argv[1];
    }

    char target[256] = "";
    sscanf(query, "target=%255s", target);

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: http://%s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to: /\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    return 0;
}