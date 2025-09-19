#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int regex_match(const char *url, const char *pattern) {
    int status;
    regex_t compiled_regex;

    if (regcomp(&compiled_regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0; // Compilation failed
    }

    status = regexec(&compiled_regex, url, (size_t) 0, NULL, 0);
    regfree(&compiled_regex);

    return status == 0;
}

const char *get_redirect_target(const char *target_url, const char *pattern) {
    static const char *default_url = "http://example.com";
    if (regex_match(target_url, pattern)) {
        return target_url;
    } else {
        return default_url;
    }
}

int main() {
    const char *target_url = "http://specific-target.com";
    const char *pattern = "^http://specific-target\\.com$";
    const char *redirect_target = get_redirect_target(target_url, pattern);
    printf("Redirect target: %s\n", redirect_target);
    return 0;
}