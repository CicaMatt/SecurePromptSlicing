#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int compile_regex(const char *pattern, regex_t *compiled_regex) {
    int reti;
    if ((reti = regcomp(compiled_regex, pattern, REG_EXTENDED)) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    return 0;
}

const char* match_redirect_url(const char *target_url, regex_t *compiled_regex) {
    regmatch_t pmatch[1];
    if (regexec(compiled_regex, target_url, 1, pmatch, 0) == 0) {
        return target_url;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    const char *pattern = "http://example\\.com/.*";
    regex_t compiled_regex;

    if (compile_regex(pattern, &compiled_regex)) {
        exit(EXIT_FAILURE);
    }

    const char *urls[] = {
        "http://example.com/path1",
        "https://another.com/path2",
        "http://example.com/path3"
    };

    for (int i = 0; i < 3; ++i) {
        const char *redirect_url = match_redirect_url(urls[i], &compiled_regex);
        printf("Redirect URL: %s\n", redirect_url);
    }

    regfree(&compiled_regex);

    return 0;
}