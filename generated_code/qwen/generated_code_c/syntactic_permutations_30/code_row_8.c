#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {
    const char *query = "target=-.example.com"; // Example query string
    const char *param = "target=";
    const char *target;
    regex_t regex;
    int reti;

    if (strstr(query, param) == NULL) {
        target = "";
    } else {
        target = strstr(query, param) + strlen(param);
    }

    const char *pattern = "^[-.]*\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to root\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    return 0;
}