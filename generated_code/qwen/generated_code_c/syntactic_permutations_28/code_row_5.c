#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.(com|org)$"

int main() {
    const char *url = "http://example.com"; // This would be your input URL
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    const char *redirect_url;
    if (!reti) {
        redirect_url = url; // Use the target URL for redirection
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL; // Use default URL for redirection
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    printf("Redirecting to: %s\n", redirect_url);

    // Free compiled regular expression if you won't use it again
    regfree(&regex);

    return 0;
}