#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

void redirect(const char *target) {
    printf("Location: %s\r\n", target);
    printf("\r\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        redirect("/");
        return 0;
    }

    const char *target = argv[1];
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "example\\.com", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        redirect("/");
        return 1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        redirect("/");
    }

    regfree(&regex);
    return 0;
}