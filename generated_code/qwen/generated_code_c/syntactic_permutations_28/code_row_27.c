#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_REGEX "^http://example\\.com/.*"

int main() {
    regex_t regex;
    const char *pattern = TARGET_REGEX;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Example target URL to check
    const char *target_url = "http://example.com/somepage";

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Match found. Redirecting to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Using default URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it again
    regfree(&regex);

    return 0;
}