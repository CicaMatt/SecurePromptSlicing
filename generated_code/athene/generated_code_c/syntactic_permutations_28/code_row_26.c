#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void compile_regex() {
    regcomp(&regex, "^https?://target\\.com/.*$", REG_EXTENDED);
}

const char *get_redirect_target(const char *url) {
    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        return url;
    } else {
        return default_url;
    }
}

int main() {
    compile_regex();
    const char *test_urls[] = {"http://target.com/path", "https://example.net"};
    for (int i = 0; i < 2; i++) {
        printf("URL: %s -> Redirect to: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }
    regfree(&regex);
    return 0;
}