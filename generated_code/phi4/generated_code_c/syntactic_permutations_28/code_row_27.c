#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://defaulturl.com"

int compile_regex(regex_t *compiled_regex, const char *pattern) {
    int reti;
    reti = regcomp(compiled_regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (reti != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int match_url(regex_t *compiled_regex, const char *target_url, char **redirect_url) {
    regmatch_t pmatch[1];
    int reti;

    if ((reti = regexec(compiled_regex, target_url, 1, pmatch, 0)) == REG_NOMATCH) {
        *redirect_url = strdup(DEFAULT_URL);
        return 0;
    } else if (reti) {
        fprintf(stderr, "Regex match failed\n");
        exit(EXIT_FAILURE);
    }

    size_t length = pmatch[0].rm_eo - pmatch[0].rm_so;
    *redirect_url = malloc(length + 1);

    if (*redirect_url == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(*redirect_url, target_url + pmatch[0].rm_so, length);
    (*redirect_url)[length] = '\0';

    return 1;
}

int main() {
    regex_t compiled_regex;
    const char *pattern = "^https?://example\\.com/.*$";
    const char *target_urls[] = {
        "http://example.com/path",
        "http://notexample.com/nothing",
        "https://example.com/anotherpath"
    };
    int num_urls = sizeof(target_urls) / sizeof(target_urls[0]);

    compile_regex(&compiled_regex, pattern);

    for (int i = 0; i < num_urls; i++) {
        char *redirect_url;
        if (match_url(&compiled_regex, target_urls[i], &redirect_url)) {
            printf("Target URL: %s\nRedirect to: %s\n", target_urls[i], redirect_url);
            free(redirect_url);
        } else {
            printf("Target URL: %s\nNo match. Default Redirect URL: %s\n", target_urls[i], DEFAULT_URL);
        }
    }

    regfree(&compiled_regex);

    return 0;
}