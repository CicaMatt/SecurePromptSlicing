#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

void compile_regex() {
    const char *pattern = "^https?://(?:www\\.)?target\\.com/.*$";
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

const char *get_redirect_url(const char *target_url) {
    int match = regexec(&regex, target_url, 0, NULL, 0);
    if (match == 0) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    compile_regex();
    const char *target_url = "http://target.com/path";
    const char *redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    target_url = "http://other.com/path";
    redirect_url = get_redirect_url(target_url);
    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}