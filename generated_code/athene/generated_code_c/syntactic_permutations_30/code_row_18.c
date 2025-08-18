#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    const char *target = argv[1];
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    regfree(&regex);
    return 0;
}