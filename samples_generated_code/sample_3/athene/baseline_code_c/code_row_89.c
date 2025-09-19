#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex() {
    const char *pattern = "^https?://target\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    regmatch_t matches[1];
    if (regexec(&regex, target_url, 1, matches, 0) == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    init_regex();
    const char *target_url = "http://target.com/path";
    const char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    // Test with a non-matching URL
    target_url = "http://other.com/path";
    redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}