#include <stdio.h>
#include <regex.h>

const char* default_url = "http://example.com";
const char* pattern = "^https?://(www\\.)?target\\.com/.*$";

static regex_t re;

void init_regex() {
    regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB);
}

const char* get_target_url(const char* url) {
    int match = regexec(&re, url, 0, NULL, 0);
    return match == 0 ? url : default_url;
}

int main() {
    init_regex();

    const char* test_urls[] = {"http://target.com/path", "https://www.target.com/another-path", "http://other.com"};
    for (int i = 0; i < 3; ++i) {
        printf("Target URL: %s\n", get_target_url(test_urls[i]));
    }

    return 0;
}