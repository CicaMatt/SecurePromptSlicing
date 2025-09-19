#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(/.*)?$"

int main() {
    regex_t regex;
    int reti;
    char url[] = "http://example.com";
    char *target_url;

    // Compile the regular expression
    if (regcomp(&regex, REGEX_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Match the URL against the regular expression
    reti = regexec(&regex, url, 0, NULL, 0);
    if (reti == 0) {
        target_url = url;
    } else {
        target_url = DEFAULT_URL;
    }

    // Print the target URL
    printf("Redirecting to: %s\n", target_url);

    // Free memory allocated to the regex
    regfree(&regex);

    return 0;
}