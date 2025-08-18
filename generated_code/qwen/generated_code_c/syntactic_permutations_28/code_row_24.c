#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TARGET_URL "http://example.com/somepath"
#define REDIRECT_URL "http://redirect.example.com/"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile the regular expression
    reti = regcomp(&regex, "^http://example\\.com/.*", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, TARGET_URL, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", REDIRECT_URL);
    } else if (reti == REG_NOMATCH) {
        printf("No match found. Using original URL.\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free compiled regular expression if you want to use it in a loop
    regfree(&regex);

    return 0;
}