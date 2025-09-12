#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    regex_t regex;
    int reti;
    const char *url = "http://example.com/somepath";
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        printf("URL matches. Redirecting to: %s\n", url);
    } else if (reti == REG_NOMATCH) {
        printf("URL does not match. Using default URL: %s\n", DEFAULT_URL);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}