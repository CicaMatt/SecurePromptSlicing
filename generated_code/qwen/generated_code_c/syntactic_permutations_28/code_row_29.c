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
        return 1;
    }

    const char *target_url = "http://example.com/somepage";
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (reti == 0) {
        printf("Redirect to: %s\n", target_url);
    } else {
        printf("Redirect to default URL: %s\n", DEFAULT_URL);
    }

    regfree(&regex);
    return 0;
}