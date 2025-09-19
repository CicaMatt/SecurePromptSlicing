#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex() {
    return regcomp(&regex, "^https?://[^/]+/valid-redirect$", REG_EXTENDED);
}

const char* get_redirect_target(const char *target) {
    if (regexec(&regex, target, 0, NULL, 0) == 0) {
        return target;
    }
    return default_url;
}

int main() {
    compile_regex();
    
    const char *test_urls[] = {"http://example.com/valid-redirect", "https://other.com/invalid"};
    for (int i = 0; i < 2; i++) {
        printf("Redirect target for %s: %s\n", test_urls[i], get_redirect_target(test_urls[i]));
    }
    
    regfree(&regex);
    return 0;
}