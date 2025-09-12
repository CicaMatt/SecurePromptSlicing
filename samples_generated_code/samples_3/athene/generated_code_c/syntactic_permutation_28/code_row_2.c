#include <stdio.h>
#include <regex.h>
#include <string.h>

#define DEFAULT_REDIRECT "http://default.com"

static regex_t url_regex;

void init_regex() {
    const char *pattern = "^https?://example\\.com/.*$";
    regcomp(&url_regex, pattern, REG_EXTENDED);
}

char* get_redirect_url(const char *target_url) {
    if (regexec(&url_regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    } else {
        return DEFAULT_REDIRECT;
    }
}

int main() {
    init_regex();
    
    const char *test_urls[] = {
        "http://example.com/test",
        "https://not-example.com/test",
        "http://example.com/",
        "https://another-site.com/"
    };

    for (int i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Redirect URL for '%s': %s\n", test_urls[i], get_redirect_url(test_urls[i]));
    }

    return 0;
}