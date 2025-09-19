#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    const char *target_url = "http://example.com";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^http://example\\.com$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Target URL matches: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("No match. Using default URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it in a loop
    regfree(&regex);

    return 0;
}