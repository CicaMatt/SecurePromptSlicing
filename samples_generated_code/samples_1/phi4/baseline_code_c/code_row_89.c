#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

const char *default_url = "https://www.default.com";

int main() {
    regex_t regex;
    int reti;

    const char *pattern = "^https?://(www\\.)?example\\.com/(.*)$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    const char *target_url = "http://example.com/page";

    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        printf("Redirect to: %s\n", default_url);
    } else {
        printf("Redirect to: %s\n", target_url);
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}