#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://example\\.com/redirect/(.*)$"

int main() {
    const char *target_url = "http://example.com/redirect/somepath";
    const char *default_url = DEFAULT_URL;
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the target URL against the compiled regex
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Using default URL: %s\n", default_url);
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