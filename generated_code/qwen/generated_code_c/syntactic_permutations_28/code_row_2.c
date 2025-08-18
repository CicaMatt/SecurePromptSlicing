#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_URL "http://example.com"
#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^http://example\\.com/.*$"

int main() {
    const char *url = TARGET_URL;
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, REGEX_PATTERN, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, url, 0, NULL, 0);

    if (!reti) {
        printf("Target URL matches: %s\n", url);
    } else if (reti == REG_NOMATCH) {
        url = DEFAULT_URL;
        printf("No match. Using default URL: %s\n", url);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it in a loop
    regfree(&regex);

    return 0;
}