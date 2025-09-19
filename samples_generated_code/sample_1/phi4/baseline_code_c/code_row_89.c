#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    int reti;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*";
    char target_url[256] = "http://example.com/page";

    // Compile regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Execute regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    
    if (!reti) {
        printf("Redirect URL: %s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("Redirect URL: %s\n", DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    // Free compiled regular expression
    regfree(&regex);

    return EXIT_SUCCESS;
}