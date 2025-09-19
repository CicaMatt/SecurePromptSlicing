#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256

int main() {
    const char *pattern = "^https?://example\\.com/.*";
    regex_t regex;
    int reti;
    char target_url[MAX_URL_LENGTH];

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Example target URL
    strcpy(target_url, "https://example.com/somepath");

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

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}