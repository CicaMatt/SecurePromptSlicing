#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_REGEX "^https?://(www\\.)?example\\.com/.*"

int main() {
    regex_t regex;
    int reti;
    const char *url = "http://example.com/somepage";
    char redirect_url[256];

    // Compile the regular expression
    reti = regcomp(&regex, TARGET_REGEX, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Execute the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        strcpy(redirect_url, url);
    } else if (reti == REG_NOMATCH) {
        strcpy(redirect_url, DEFAULT_URL);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    // Free the compiled regular expression
    regfree(&regex);

    printf("Redirect URL: %s\n", redirect_url);

    return 0;
}