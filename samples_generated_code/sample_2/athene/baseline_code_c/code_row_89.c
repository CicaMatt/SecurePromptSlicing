#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex() {
    const char *pattern = "^https?://example\\.com/redirected$";
    return regcomp(&regex, pattern, REG_EXTENDED);
}

const char *get_redirect_url(const char *target_url) {
    int match_result;
    if ((match_result = regexec(&regex, target_url, 0, NULL, 0)) == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    if (compile_regex()) {
        fprintf(stderr, "Regex compilation failed\n");
        exit(1);
    }

    const char *target_url = "http://example.com/redirected";
    const char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}