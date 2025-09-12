#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    char *pattern = "^https?://.*$";
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Example URLs to test
    char *urls[] = {"http://example.com", "https://another-example.com", "ftp://invalid-url.com"};
    size_t num_urls = sizeof(urls) / sizeof(urls[0]);

    for (size_t i = 0; i < num_urls; i++) {
        const char *url = urls[i];
        regmatch_t match;

        // Execute the regular expression
        reti = regexec(&regex, url, 1, &match, 0);
        
        if (!reti) {
            printf("URL %s matches the pattern. Redirect URL: %s\n", url, url);
        } else if (reti == REG_NOMATCH) {
            printf("URL %s does not match the pattern. Redirect URL: %s\n", url, DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}