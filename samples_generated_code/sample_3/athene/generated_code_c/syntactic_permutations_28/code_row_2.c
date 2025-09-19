#include <stdio.h>
#include <regex.h>
#include <string.h>

#define DEFAULT_URL "http://default.example.com"

const char *redirect_url(const char *url, const char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return DEFAULT_URL;
    }

    int match = regexec(&regex, url, 0, NULL, 0);
    regfree(&regex);

    if (match == 0) {
        return url;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    const char *url_to_check = "http://example.com";
    const char *pattern = "^http://example\\.com$";

    const char *redirect = redirect_url(url_to_check, pattern);
    printf("Redirect to: %s\n", redirect);

    return 0;
}