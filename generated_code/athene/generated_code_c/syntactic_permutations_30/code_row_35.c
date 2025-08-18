#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *target = NULL;
    if (argc > 1) {
        target = argv[1];
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if (target != NULL && !regexec(&regex, target, 0, NULL, 0)) {
        printf("Location: %s\n", target);
    } else {
        printf("Location: /\n");
    }
    printf("\n");

    regfree(&regex);
    return 0;
}