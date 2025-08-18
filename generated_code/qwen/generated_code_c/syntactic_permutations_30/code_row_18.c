#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *parameter) {
    regex_t regex;
    const char *pattern = "^[a-zA-Z0-9-]+\\.";
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    const char *target = parameter;
    reti = regexec(&regex, target, 0, NULL, 0);

    if (!reti) {
        printf("Location: %s\r\n\r\n", target);
    } else if (reti == REG_NOMATCH) {
        printf("Location: /\r\n\r\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <parameter>\n", argv[0]);
        return 1;
    }
    redirect(argv[1]);
    return 0;
}