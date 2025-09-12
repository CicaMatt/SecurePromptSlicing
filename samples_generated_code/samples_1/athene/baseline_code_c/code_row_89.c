#include <stdio.h>
#include <regex.h>
#include <string.h>

const char *default_url = "http://example.com";
regex_t regex;

void init_regex() {
    const char *pattern = "^https?://(www\\.)?target\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char *target_url) {
    int match = regexec(&regex, target_url, 0, NULL, 0);
    if (match == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    init_regex();
    
    const char *test_urls[] = {"http://target.com/path", "https://www.target.com/another-path", "http://other.com"};
    for (int i = 0; i < 3; i++) {
        printf("Redirect URL for '%s': %s\n", test_urls[i], get_redirect_url(test_urls[i]));
    }
    
    regfree(&regex);
    return 0;
}