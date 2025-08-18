#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

void process_url(const char *url) {
    regex_t reg;
    int reti;

    // Compile regular expression
    reti = regcomp(&reg, "^https?://(www\\.)?example\\.com/.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&reg, url, 0, NULL, 0);

    if (!reti) {
        printf("Redirect to: %s\n", url); // URL matches the pattern
    } else if (reti == REG_NOMATCH) {
        printf("Redirect to: %s\n", DEFAULT_URL); // URL does not match the pattern
    } else {
        char msgbuf[100];
        regerror(reti, &reg, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use the regex_t again
    regfree(&reg);
}

int main() {
    const char *test_urls[] = {
        "http://www.example.com/path",
        "https://example.com/anotherpath",
        "http://unrelated.com/test",
        NULL
    };

    for (const char **url = test_urls; *url != NULL; url++) {
        process_url(*url);
    }

    return 0;
}