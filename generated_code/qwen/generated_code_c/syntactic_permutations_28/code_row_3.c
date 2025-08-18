#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];
    const char *url = "http://example.com/somepath";
    const char *redirect_url;

    // Compile regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        redirect_url = url;
    } else if (reti == REG_NOMATCH) {
        redirect_url = DEFAULT_URL;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Print the result
    printf("Redirect URL: %s\n", redirect_url);

    // Free compiled regular expression if you want to use it in a loop
    regfree(&regex);

    return 0;
}