#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_REGEX "^https?://example\\.com/.*"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *target_url = "http://example.com/test";
    const char *redirect_url;

    // Compile regular expression
    reti = regcomp(&regex, TARGET_REGEX, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
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

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    printf("Redirecting to: %s\n", redirect_url);

    return 0;
}