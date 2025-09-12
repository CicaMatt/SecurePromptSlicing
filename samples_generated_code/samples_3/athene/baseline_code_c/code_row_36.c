#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int compile_regex(const char *pattern) {
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        size_t len = regerror(ret, &regex, NULL, 0);
        char *buf = malloc(len);
        regerror(ret, &regex, buf, len);
        fprintf(stderr, "Regex compilation failed: %s\n", buf);
        free(buf);
        return -1;
    }
    return 0;
}

const char *get_redirect_url(const char *target_url) {
    int ret = regexec(&regex, target_url, 0, NULL, 0);
    if (ret == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    const char *pattern = "^https?://example\\.org/.*$";
    if (compile_regex(pattern) != 0) {
        return 1;
    }

    const char *target_url = "http://example.org/path/to/resource";
    const char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}