#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REGEX_PATTERN "^https?://(www\\.)?example\\.com/.*"

void process_url(const char *url) {
    regex_t regex;
    int ret;

    // Compile the regular expression
    ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Match the URL against the compiled regex
    ret = regexec(&regex, url, 0, NULL, 0);

    if (!ret) {
        printf("Redirect target: %s\n", url); // Use the matching URL as redirect target
    } else if (ret == REG_NOMATCH) {
        printf("No match for URL: %s\n", url);
    } else {
        char msgbuf[100];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main() {
    const char *urls[] = {
        "https://www.example.com/page1",
        "http://example.com/page2",
        "https://notexample.com/notpage",
        "https://example.com/",
        NULL
    };

    for (const char **url = urls; *url != NULL; url++) {
        process_url(*url);
    }

    return 0;
}