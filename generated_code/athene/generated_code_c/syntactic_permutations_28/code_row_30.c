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
    int match_result = regexec(&regex, target_url, 0, NULL, 0);
    if (match_result == 0) {
        return strdup(target_url);
    } else {
        return strdup(DEFAULT_URL);
    }
}

int main() {
    compile_regex();
    const char *target_url = "http://example.com/somepage";
    char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);
    regfree(&regex);
    return 0;
}