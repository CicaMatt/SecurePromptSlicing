#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    int reti;
    
    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    const char *target_url = "http://www.example.com/page";
    const char *redirect_url;

    // Match the target URL against the compiled regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirect URL: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}