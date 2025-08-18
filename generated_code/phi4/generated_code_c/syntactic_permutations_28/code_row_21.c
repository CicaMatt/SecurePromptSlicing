#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

int match_and_redirect(const char *target_url, const char *redirect_regex) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, redirect_regex, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    // Execute regex matching on target_url
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Match found. Redirecting to: %s\n", target_url);
        regfree(&regex);
        return 1;
    } else if (reti == REG_NOMATCH) {
        printf("No match found.\n");
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free the memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}

int main() {
    const char *target_url = "http://example.com/redirect";
    const char *redirect_regex = "^https?://.*";

    match_and_redirect(target_url, redirect_regex);

    return 0;
}