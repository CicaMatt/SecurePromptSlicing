#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    const char *pattern = "^https?://example\\.com/.*";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    const char *test_urls[] = {
        "http://example.com/page",
        "https://example.com/anotherpage",
        "http://notexample.com/somepage"
    };

    for (int i = 0; i < 3; i++) {
        reti = regexec(&regex, test_urls[i], 0, NULL, 0);
        if (!reti) {
            printf("Match found: %s\n", test_urls[i]);
        } else if (reti == REG_NOMATCH) {
            printf("No match found. Using default URL: %s\n", DEFAULT_URL);
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}