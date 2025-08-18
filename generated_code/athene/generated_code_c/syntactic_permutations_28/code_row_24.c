#include <stdio.h>
#include <regex.h>

int main() {
    const char *target_url = "http://example.com";
    const char *pattern = "^http://example\\.com$";
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, target_url, 0, NULL, 0);
    if (!reti) {
        printf("Redirect to: %s\n", target_url);
    } else {
        printf("No redirect\n");
    }

    regfree(&regex);
    return 0;
}