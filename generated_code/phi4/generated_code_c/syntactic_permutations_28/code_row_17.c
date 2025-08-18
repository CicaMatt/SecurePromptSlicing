#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "https://www.default.com"

int main() {
    const char *pattern = "^https?://example\\.com";
    regex_t regex;
    int ret;

    // Compile the regular expression
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    const char *test_url = "https://www.example.com/page";
    char buffer[256];
    regmatch_t match;

    // Check if the test URL matches the pattern
    ret = regexec(&regex, test_url, 1, &match, 0);

    if (!ret) {
        snprintf(buffer, sizeof(buffer), "Redirecting to: %s", test_url);
    } else if (ret == REG_NOMATCH) {
        snprintf(buffer, sizeof(buffer), "Redirecting to default URL: %s", DEFAULT_URL);
    } else {
        regfree(&regex);
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }

    printf("%s\n", buffer);

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}