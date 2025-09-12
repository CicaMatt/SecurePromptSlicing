#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define TARGET_URL "http://example.com/some/path"
#define REDIRECT_PATTERN "^http://example\\.com/some/.*$"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression once
    reti = regcomp(&regex, REDIRECT_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Use the compiled regular expression to match the target URL
    reti = regexec(&regex, TARGET_URL, 0, NULL, 0);
    if (!reti) {
        printf("Target URL matches. Redirecting to: %s\n", TARGET_URL);
    } else if (reti == REG_NOMATCH) {
        printf("Target URL does not match.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}