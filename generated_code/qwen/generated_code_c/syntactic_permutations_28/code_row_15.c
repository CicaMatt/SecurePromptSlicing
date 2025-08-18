#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define REGEX_PATTERN "^https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(/.*)?$"

int main() {
    const char *url = "http://example.com";
    const char *redirect_url;
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        redirect_url = url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    printf("Redirect URL: %s\n", redirect_url);

    return 0;
}