#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    regex_t regex;
    const char *pattern = "^https?://[^/]+/valid-redirect$";
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) return 1;

    const char *target_url = argv[1];
    int match_result = regexec(&regex, target_url, 0, NULL, 0);

    if (match_result == 0) {
        printf("%s\n", target_url);
    } else {
        printf("%s\n", default_url);
    }

    regfree(&regex);
    return 0;
}