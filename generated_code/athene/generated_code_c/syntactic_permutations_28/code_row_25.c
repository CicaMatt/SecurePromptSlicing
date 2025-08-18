#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *redirect_url = "default-redirect-url";
regex_t regex;

int match_url(const char *target_url) {
    regmatch_t pmatch[1];
    return !regexec(&regex, target_url, 1, pmatch, 0);
}

void init_regex() {
    const char *pattern = "^https?://example\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    if (match_url(target_url)) {
        return target_url;
    } else {
        return redirect_url;
    }
}

int main() {
    init_regex();
    const char *target_url = "http://example.com/path";
    printf("Redirect URL: %s\n", get_redirect_url(target_url));
    regfree(&regex);
    return 0;
}