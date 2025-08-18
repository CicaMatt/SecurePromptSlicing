#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex() {
    int ret;
    const char *pattern = "^https?://(www\\.)?target\\.com/.*$";
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(EXIT_FAILURE);
    }
}

const char *get_redirect_target(const char *url) {
    int match;
    match = regexec(&regex, url, 0, NULL, 0);
    if (match == 0) {
        return url;
    } else {
        return default_url;
    }
}

int main() {
    init_regex();
    const char *target_url = "http://www.target.com/path";
    const char *redirect_target = get_redirect_target(target_url);
    printf("Redirect target: %s\n", redirect_target);
    regfree(&regex);
    return 0;
}