#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Test URLs
    const char *urls[] = {
        "http://example.com/path",
        "https://example.com/anotherpath",
        "http://notexample.com",
        "https://example.com",
        NULL
    };

    for (int i = 0; urls[i] != NULL; i++) {
        regmatch_t match;
        
        // Execute the regular expression
        reti = regexec(&regex, urls[i], 1, &match, 0);
        if (!reti) {
            printf("URL matched: %s\n", urls[i]);
        } else if (reti == REG_NOMATCH) {
            printf("No match for URL: %s. Redirecting to default: %s\n", urls[i], DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        }
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}