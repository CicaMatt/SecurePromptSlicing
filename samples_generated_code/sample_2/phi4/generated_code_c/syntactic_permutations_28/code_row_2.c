#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int compile_regex(regex_t *re, const char *pattern) {
    return regcomp(re, pattern, REG_EXTENDED);
}

char* redirect_url(const char *url, regex_t *re, const char *default_url) {
    int status;
    if ((status = regexec(re, url, 0, NULL, 0)) == 0) {
        // URL matches the regular expression
        return strdup(url);
    } else if (status != REG_NOMATCH) {
        fprintf(stderr, "Regex match failed\n");
        exit(EXIT_FAILURE);
    }

    // URL does not match, use default
    return strdup(default_url);
}

int main() {
    regex_t re;
    const char *pattern = "^https?://(www\\.)?example\\.com/.*$";  // Example pattern for matching URLs

    if (compile_regex(&re, pattern) != 0) {
        fprintf(stderr, "Could not compile regular expression\n");
        exit(EXIT_FAILURE);
    }

    const char *urls[] = {
        "http://www.example.com/path",
        "https://example.com/anotherpath",
        "http://notexample.com",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        char* result_url = redirect_url(urls[i], &re, DEFAULT_URL);
        printf("Original URL: %s\nRedirect URL: %s\n", urls[i], result_url);
        free(result_url);
    }

    regfree(&re);
    return 0;
}