#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_URL "http://example.com/some/path"
#define REDIRECT_URL "http://redirected-url.com"

int main() {
    regex_t regex;
    int reti;
    const char *pattern = "^http://example\\.com/.*$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, TARGET_URL, 0, NULL, 0);
    if (!reti) {
        printf("Match found. Redirecting to: %s\n", REDIRECT_URL);
    } else if (reti == REG_NOMATCH) {
        printf("No match. URL remains unchanged.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);

    return 0;
}