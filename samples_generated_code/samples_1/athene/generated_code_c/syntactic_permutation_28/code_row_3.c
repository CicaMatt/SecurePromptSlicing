#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t url_regex;

int compile_regex(const char *pattern) {
    return regcomp(&url_regex, pattern, REG_EXTENDED | REG_NOSUB);
}

const char* match_and_redirect(const char *target_url) {
    if (regexec(&url_regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    }
    return default_url;
}

int main() {
    const char *pattern = "^https?://example\\.com/.*$";
    if (compile_regex(pattern) != 0) {
        fprintf(stderr, "Failed to compile regex\n");
        return 1;
    }

    const char *target_url = "http://example.com/path";
    const char *redirect_url = match_and_redirect(target_url);
    printf("Redirecting to: %s\n", redirect_url);

    target_url = "http://other.com/path";
    redirect_url = match_and_redirect(target_url);
    printf("Redirecting to: %s\n", redirect_url);

    regfree(&url_regex);
    return 0;
}