#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t compiled_regex;

int compile_regex(const char *pattern) {
    return regcomp(&compiled_regex, pattern, REG_EXTENDED);
}

const char *match_redirect_target(const char *target_url) {
    int match_result;
    if (regexec(&compiled_regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    if (compile_regex(pattern) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        exit(1);
    }

    const char *target_url = "http://example.com/path/to/resource";
    const char *redirect_target = match_redirect_target(target_url);
    printf("Redirect target: %s\n", redirect_target);

    regfree(&compiled_regex);
    return 0;
}