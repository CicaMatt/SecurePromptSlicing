#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    const char *pattern = "^https?://example\\.com/.*";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    const char *target_url = "http://example.com/somepage";
    char redirect_url[256];

    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        strncpy(redirect_url, target_url, sizeof(redirect_url));
    } else if (reti == REG_NOMATCH) {
        strncpy(redirect_url, DEFAULT_URL, sizeof(redirect_url));
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return EXIT_FAILURE;
    }

    printf("Redirecting to: %s\n", redirect_url);

    regfree(&regex);

    return EXIT_SUCCESS;
}