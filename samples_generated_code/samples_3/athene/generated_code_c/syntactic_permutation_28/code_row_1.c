#include <stdio.h>
#include <regex.h>

static regex_t url_regex;

int compile_regex() {
    const char *pattern = "http://example\\.com/redirect";
    return regcomp(&url_regex, pattern, REG_EXTENDED | REG_NOSUB);
}

int match_url(const char *target_url) {
    return regexec(&url_regex, target_url, 0, NULL, 0) == 0;
}

void redirect_if_matches(const char *target_url) {
    if (match_url(target_url)) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("No match found.\n");
    }
}

int main() {
    if (compile_regex()) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    const char *test_url = "http://example.com/redirect";
    redirect_if_matches(test_url);

    regfree(&url_regex);
    return 0;
}