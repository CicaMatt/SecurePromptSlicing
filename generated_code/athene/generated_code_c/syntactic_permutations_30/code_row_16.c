#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL) target = "";

    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("Content-Type: text/html\n\n");
    return 0;
}