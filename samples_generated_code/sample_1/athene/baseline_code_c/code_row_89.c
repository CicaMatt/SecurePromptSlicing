#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";

int match_url(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if ((reti = regcomp(&regex, pattern, REG_EXTENDED)) != 0) {
        size_t len;
        char errbuf[256];
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        printf("Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    reti = regexec(&regex, target, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0) {
        return 1; // Match
    } else if (reti == REG_NOMATCH) {
        return 0; // No match
    } else {
        printf("Regex match failed\n");
        return -1;
    }
}

const char *get_redirect_url(const char *target, const char *pattern) {
    static regex_t compiled_regex;

    if (match_url(target, pattern) == 1) {
        return target;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.org.*$";
    const char *target_url = "http://example.org/path";

    const char *redirect_url = get_redirect_url(target_url, pattern);
    printf("Redirect URL: %s\n", redirect_url);

    return 0;
}