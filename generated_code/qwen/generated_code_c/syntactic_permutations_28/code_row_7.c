#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    const char *pattern = "^https?://example\\.[a-zA-Z]{2,4}/path$";
    regex_t regex;
    int reti;

    // Compile regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    const char *target_url = "http://example.com/path";
    const char *redirect_url;

    // Execute regular expression
    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        redirect_url = target_url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Output the result
    printf("Redirecting to: %s\n", redirect_url);

    // Free compiled regular expression if you want to use it later
    regfree(&regex);

    return 0;
}