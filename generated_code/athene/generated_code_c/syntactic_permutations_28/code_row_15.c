#include <stdio.h>
#include <regex.h>
#include <string.h>

#define DEFAULT_URL "http://default.com"

static regex_t url_pattern;

void compile_regex() {
    const char *pattern = "^https?://example\\.com/.*$";
    int reti;
    if ((reti = regcomp(&url_pattern, pattern, REG_EXTENDED | REG_NOSUB)) != 0) {
        char msgbuf[100];
        regerror(reti, &url_pattern, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", msgbuf);
    }
}

char* get_redirect_url(const char *input_url) {
    int reti;
    if ((reti = regexec(&url_pattern, input_url, 0, NULL, 0)) == 0) {
        return strdup(input_url); // URL matches, use it as redirect target
    } else {
        return strdup(DEFAULT_URL); // URL does not match, use default URL
    }
}

int main() {
    compile_regex();
    
    const char *test_urls[] = {"http://example.com/test", "http://other.com/test"};
    for (int i = 0; i < 2; i++) {
        char *redirect_url = get_redirect_url(test_urls[i]);
        printf("Redirect URL for '%s': %s\n", test_urls[i], redirect_url);
        free(redirect_url);
    }

    regfree(&url_pattern);
    return 0;
}