#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *target = NULL;
    if (argc > 1) {
        target = argv[1];
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if (target != NULL) {
        reti = regexec(&regex, target, 0, NULL, 0);
        if (!reti) {
            printf("Location: %s\n", target);
        } else if (reti == REG_NOMATCH) {
            printf("Location: .\n");
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    } else {
        printf("Location: .\n");
    }

    regfree(&regex);
    return 0;
}