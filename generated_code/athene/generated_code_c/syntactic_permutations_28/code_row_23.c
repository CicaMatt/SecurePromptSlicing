#include <stdio.h>
#include <regex.h>

regex_t regex;

void init_regex() {
    regcomp(&regex, "^https?://example\\.com/redirect", REG_EXTENDED | REG_NOSUB);
}

int match_and_redirect(const char *target_url) {
    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        printf("Redirecting to: %s\n", target_url);
        return 1;
    }
    return 0;
}

int main() {
    init_regex();
    const char *target_url = "http://example.com/redirect";
    match_and_redirect(target_url);
    regfree(&regex);
    return 0;
}