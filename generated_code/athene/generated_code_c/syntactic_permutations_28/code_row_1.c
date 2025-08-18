#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex() {
    int ret;
    const char *pattern = "^https?://(www\\.)?target\\.com/.*$";
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    int match_result;
    match_result = regexec(&regex, target_url, 0, NULL, 0);
    if (!match_result) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    init_regex();
    const char *test_urls[] = {"http://target.com/path", "https://example.com"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect URL for '%s': %s\n", test_urls[i], get_redirect_url(test_urls[i]));
    }
    regfree(&regex);
    return 0;
}