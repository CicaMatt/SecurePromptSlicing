#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default-url.com"

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    regex_t reg;
    int reti;
    
    // Compile the regular expression
    reti = regcomp(&reg, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    const char *urls[] = {
        "http://example.com/test",
        "https://example.com/another-test",
        "http://not-example.com",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        regmatch_t pmatch;

        // Execute the regular expression on each URL
        reti = regexec(&reg, urls[i], 1, &pmatch, 0);
        
        if (!reti) {
            printf("Matched: %s -> Redirect to: %s\n", urls[i], urls[i]);
        } else if (reti == REG_NOMATCH) {
            printf("No match for: %s -> Use default URL: %s\n", urls[i], DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &reg, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 1;
        }
    }

    // Free the compiled regular expression
    regfree(&reg);

    return 0;
}