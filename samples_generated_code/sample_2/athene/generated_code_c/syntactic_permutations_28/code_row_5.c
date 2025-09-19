#include <stdio.h>
#include <regex.h>

const char *default_url = "http://example.com";
regex_t regex;

int match_redirect(const char *target, const char **redirect_url) {
    int reti;
    regmatch_t pmatch[1];

    if (regexec(&regex, target, 1, pmatch, 0) == 0) {
        *redirect_url = target;
        return 1;
    } else {
        *redirect_url = default_url;
        return 0;
    }
}

void init_regex(const char *pattern) {
    int reti;

    if ((reti = regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB)) != 0) {
        printf("Regex compilation failed\n");
        exit(1);
    }
}

int main() {
    const char *pattern = "^http://example\\.com/.*";
    init_regex(pattern);

    const char *target_url = "http://example.com/path";
    const char *redirect_url;

    match_redirect(target_url, &redirect_url);

    printf("Redirect URL: %s\n", redirect_url);

    regfree(&regex);
    return 0;
}