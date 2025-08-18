#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define REGEX_PATTERN "^https?://example\\.com/.*"

static regex_t compiled_regex;

void init_regex() {
    int ret = regcomp(&compiled_regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

char* get_redirect_url(const char *target_url) {
    int match;
    regmatch_t pmatch[1];
    
    match = regexec(&compiled_regex, target_url, 1, pmatch, 0);
    if (match == 0) {
        return strdup(target_url);
    } else {
        return strdup(DEFAULT_URL);
    }
}

int main(int argc, char **argv) {
    init_regex();
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target-url>\n", argv[0]);
        exit(1);
    }

    char *redirect_url = get_redirect_url(argv[1]);
    printf("Redirect URL: %s\n", redirect_url);
    free(redirect_url);

    regfree(&compiled_regex);
    return 0;
}