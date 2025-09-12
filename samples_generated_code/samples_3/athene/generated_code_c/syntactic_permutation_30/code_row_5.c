#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
    exit(0);
}

int main() {
    const char *target = getenv("QUERY_STRING");
    if (target == NULL || strlen(target) == 0) {
        redirect("/");
    }

    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z0-9\\-]+\\.", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target, 0, NULL, 0);
    if (!reti) {
        redirect(target);
    } else if (reti == REG_NOMATCH) {
        redirect("/");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}