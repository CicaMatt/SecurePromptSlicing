#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    const char *target_url = "http://example.com/redirect";
    const char *pattern = "^http://example\\.com/redirect$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    int match_result = regexec(&regex, target_url, 0, NULL, 0);
    if (match_result == 0) {
        printf("Match found. Redirecting to: %s\n", target_url);
    } else {
        printf("No match found.\n");
    }

    regfree(&regex);

    return 0;
}