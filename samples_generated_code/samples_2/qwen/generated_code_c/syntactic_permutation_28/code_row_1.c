#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    const char *target_url = "http://example.com/somepage";
    regex_t regex;
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, TARGET_PATTERN, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the target URL against the compiled pattern
    reti = regexec(&regex, target_url, 0, NULL, 0);

    // Check if the match was successful
    if (!reti) {
        printf("Redirecting to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Redirecting to default URL: %s\n", DEFAULT_URL);
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