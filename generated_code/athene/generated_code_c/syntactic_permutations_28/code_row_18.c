#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";

int match_url(const char *target, const char *pattern) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    reti = regexec(&regex, target, (size_t) 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}

const char *get_redirect_url(const char *target, const char *pattern) {
    if (match_url(target, pattern)) {
        return target;
    } else {
        return default_url;
    }
}

int main() {
    const char *target = "http://specific-target.com";
    const char *pattern = "^http://specific-target\\.com$";

    const char *redirect_url = get_redirect_url(target, pattern);
    printf("Redirect URL: %s\n", redirect_url);

    return 0;
}