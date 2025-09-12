#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "https://default.url"

int main() {
    regex_t reg;
    char *pattern = "^https?://example\\.com/.*$";
    int reti;

    // Compile the regular expression
    if (regcomp(&reg, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Test strings
    char *urls[] = {
        "https://example.com/path",
        "http://example.com/anotherpath",
        "https://notexample.com/somepath",
        "https://example.org/notvalid"
    };
    
    size_t num_urls = sizeof(urls) / sizeof(urls[0]);

    for (size_t i = 0; i < num_urls; i++) {
        regmatch_t match;
        
        // Execute the regular expression
        reti = regexec(&reg, urls[i], 1, &match, 0);

        if (!reti) {
            printf("Redirect to: %s\n", urls[i]);
        } else if (reti == REG_NOMATCH) {
            printf("Redirect to: %s\n", DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &reg, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&reg);

    return 0;
}