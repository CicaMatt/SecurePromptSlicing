#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    const char *target_url = "http://example.com/somepath";
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Redirect to default URL: %s\n", DEFAULT_URL);
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