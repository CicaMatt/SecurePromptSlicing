#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    const char *pattern = "^https?://example\\.com/.*";
    const char *target_url = "http://example.com/test";
    const char *redirect_target;
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Match the target URL against the compiled regex
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (reti == 0) {
        redirect_target = target_url;
    } else if (reti == REG_NOMATCH) {
        redirect_target = DEFAULT_URL;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Print the redirect target
    printf("Redirect to: %s\n", redirect_target);

    // Free compiled regex
    regfree(&regex);

    return 0;
}