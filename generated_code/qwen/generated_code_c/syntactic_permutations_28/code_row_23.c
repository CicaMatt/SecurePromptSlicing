#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_URL "http://example.com/old-page"
#define REDIRECT_URL "http://example.com/new-page"
#define REGEX_PATTERN "^http://example\\.com/old-page$"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if the target URL matches the pattern
    reti = regexec(&regex, TARGET_URL, 0, NULL, 0);
    if (!reti) {
        printf("Redirecting to: %s\n", REDIRECT_URL);
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}