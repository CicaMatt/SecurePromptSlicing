#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define REGEX_PATTERN "^https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(/[a-zA-Z0-9._%+-]*)*$"

int main() {
    regex_t regex;
    const char *url = "http://example.com";
    const char *result_url;

    if (regcomp(&regex, REGEX_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regular expression.\n");
        exit(1);
    }

    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        result_url = url;
    } else {
        result_url = DEFAULT_URL;
    }

    printf("Redirecting to: %s\n", result_url);

    regfree(&regex);
    return 0;
}