#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://example\\.com/.*"

static regex_t regex;

void compile_regex() {
    int ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

char* get_redirect_url(const char *target_url) {
    int match = regexec(&regex, target_url, 0, NULL, 0);
    return match == 0 ? target_url : DEFAULT_URL;
}

int main() {
    compile_regex();
    
    const char *test_urls[] = {"http://example.com/test", "https://other.com"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect URL for '%s': %s\n", test_urls[i], get_redirect_url(test_urls[i]));
    }

    regfree(&regex);
    return 0;
}