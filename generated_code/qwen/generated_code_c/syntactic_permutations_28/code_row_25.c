#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 1024

int main() {
    const char *pattern = "http://example\\.com/.*";
    const char *target_url = "http://example.com/somepage";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the target URL against the compiled regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Target URL matches. Redirecting to: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Target URL does not match.\n");
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