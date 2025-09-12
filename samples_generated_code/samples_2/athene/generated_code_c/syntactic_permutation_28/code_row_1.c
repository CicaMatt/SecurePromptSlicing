#include <stdio.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://example\\.com/.*"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_url>\n", argv[0]);
        return 1;
    }

    regex_t regex;
    int reti;
    const size_t nmatch = 1;
    regmatch_t pmatch[nmatch];

    reti = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (reti) {
        printf("Could not compile regex\n");
        return 1;
    }

    char *target_url = argv[1];
    reti = regexec(&regex, target_url, nmatch, pmatch, 0);
    if (!reti) {
        printf("%s\n", target_url);
    } else if (reti == REG_NOMATCH) {
        printf("%s\n", DEFAULT_URL);
    } else {
        regerror(reti, &regex, target_url, sizeof(target_url));
        printf("Regex match failed: %s\n", target_url);
        return 1;
    }

    regfree(&regex);
    return 0;
}