#include <stdio.h>
#include <regex.h>

const char* default_url = "http://default.com";
const char* pattern = "^https?://example\\.com/.*$";
regex_t regex;

void init_regex() {
    regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
}

const char* get_redirect_target(const char* target_url) {
    int match_result = regexec(&regex, target_url, 0, NULL, 0);
    return (match_result == 0) ? "http://redirect.com" : default_url;
}

int main() {
    init_regex();
    
    const char* test_urls[] = {"http://example.com/path", "https://notexample.com"};
    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Target URL: %s -> Redirect to: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}