#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REGEX_PATTERN "^https?://example\\.com/.*$"
#define TARGET_URL "http://target.example.com"

int main() {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Test URLs against the compiled regular expression
    const char *urls[] = {
        "http://example.com/page1",
        "https://example.com/resource",
        "http://not-example.com",
        "https://example.org/home",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        reti = regexec(&regex, urls[i], 0, NULL, 0);
        if (!reti) {
            printf("URL '%s' matches the pattern. Redirecting to: %s\n", urls[i], TARGET_URL);
        } else if (reti == REG_NOMATCH) {
            printf("URL '%s' does not match the pattern.\n", urls[i]);
        } else {
            regerror(reti, &regex, NULL, 0);
            fprintf(stderr, "Regex match failed for some reason\n");
            exit(1);
        }
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&regex);

    return 0;
}