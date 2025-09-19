#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *pattern = "^https?://example\\.com/.*";
    const char *target_url = "http://example.com/test";
    const char *redirect_url;

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        redirect_url = target_url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Print the result
    printf("Redirect URL: %s\n", redirect_url);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);

    return 0;
}