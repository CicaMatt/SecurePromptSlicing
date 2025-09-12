#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default-url.com"

void handle_redirect(const char *url) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile the regular expression for the target URL pattern
    reti = regcomp(&regex, "^https?://example\\.com/.*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression on the input URL
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        // URL matches, use it as the redirect target
        printf("Redirecting to: %s\n", url);
    } else if (reti == REG_NOMATCH) {
        // URL does not match, use default URL
        printf("Redirecting to: %s\n", DEFAULT_URL);
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the memory allocated to the regex
    regfree(&regex);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    handle_redirect(argv[1]);
    return 0;
}