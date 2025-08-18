#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.com/redirect/(.*)$"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *target_url = "http://example.com/redirect/newpage";
    const char *redirect_url;

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        redirect_url = target_url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Print the result
    printf("Redirecting to: %s\n", redirect_url);

    // Free memory allocated to regex
    regfree(&regex);

    return 0;
}