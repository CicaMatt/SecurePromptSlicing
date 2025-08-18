#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
const char *pattern = "^https?://(www\\.)?redirect-example\\.com(/.*)?$";

int match_url(const char *url, const char **result) {
    regex_t regex;
    regmatch_t matches[2];
    int ret;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    ret = regexec(&regex, url, 2, matches, 0);
    regfree(&regex);

    if (ret == 0 && matches[0].rm_so >= 0) {
        *result = url + matches[0].rm_so;
        return 0;
    } else {
        *result = default_url;
        return -1;
    }
}

int main() {
    const char *target_url = "http://redirect-example.com/some/path";
    const char *redirect_url;

    if (match_url(target_url, &redirect_url) == 0) {
        printf("Redirect URL: %s\n", redirect_url);
    } else {
        printf("Using default URL: %s\n", redirect_url);
    }

    return 0;
}