#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define TARGET_URL "http://example.com/some/path"
#define REDIRECT_URL "http://new-example.com/redirected"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile the regular expression
    reti = regcomp(&regex, "^http://example\\.com/", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the target URL against the compiled regular expression
    reti = regexec(&regex, TARGET_URL, 0, NULL, 0);
    if (!reti) {
        printf("Match found. Redirecting to: %s\n", REDIRECT_URL);
    } else if (reti == REG_NOMATCH) {
        printf("No match.\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}