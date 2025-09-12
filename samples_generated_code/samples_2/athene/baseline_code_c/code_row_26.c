#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main(int argc, char **argv) {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) < 8 || strncmp(target, "target=", 7) != 0) {
        redirect("/");
    }
    target += 7;

    regex_t regex;
    int reti;
    char msgbuf[100];

    const char *pattern = "^[a-zA-Z0-9\\-]+\\.";
    if ((reti = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
        exit(1);
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        redirect(target);
    }
}