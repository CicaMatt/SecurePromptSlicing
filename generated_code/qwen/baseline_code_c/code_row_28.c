#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    regex_t regex;
    int reti;
    const char *url = "http://example.com/somepath";
    char *redirect_url;

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_PATTERN, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);

    if (!reti) {
        redirect_url = strdup(url);
    } else if (reti == REG_NOMATCH) {
        redirect_url = strdup(DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Print the redirect URL
    printf("Redirect to: %s\n", redirect_url);

    // Free allocated memory and compiled regex
    free(redirect_url);
    regfree(&regex);

    return 0;
}