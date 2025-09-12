#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://example\\.com/redirect/(.*)$"

int main() {
    const char *url = "http://example.com/redirect/somepage";
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    regmatch_t pmatch[2];
    reti = regexec(&regex, url, 2, pmatch, 0);

    const char *redirect_url;
    if (!reti) {
        // URL matches, use as redirect target
        redirect_url = url;
    } else if (reti == REG_NOMATCH) {
        // No match, use default URL
        redirect_url = DEFAULT_URL;
    } else {
        // Some other error
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    printf("Redirecting to: %s\n", redirect_url);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}