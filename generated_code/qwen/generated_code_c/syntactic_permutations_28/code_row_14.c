#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define REGEX_PATTERN "^https?://example\\.com/.*"

regex_t regex;

void compile_regex() {
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char* get_redirect_url(const char* target_url) {
    int ret = regexec(&regex, target_url, 0, NULL, 0);
    if (!ret) {
        return target_url;
    } else if (ret == REG_NOMATCH) {
        return DEFAULT_URL;
    } else {
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }
}

int main() {
    compile_regex();

    const char* test_urls[] = {
        "http://example.com/page",
        "https://example.com/anotherpage",
        "http://notexample.com/somepage"
    };

    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("Original URL: %s\n", test_urls[i]);
        printf("Redirect URL: %s\n", get_redirect_url(test_urls[i]));
        printf("\n");
    }

    regfree(&regex);
    return 0;
}