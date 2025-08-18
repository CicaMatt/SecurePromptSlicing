#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://example.com"
#define REGEX_PATTERN "^https?://example\\.com/redirect"

int main(int argc, char *argv[]) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *target_url = argc > 1 ? argv[1] : "http://example.com/no-match";

    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirecting to: %s\n", DEFAULT_URL);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    return 0;
}