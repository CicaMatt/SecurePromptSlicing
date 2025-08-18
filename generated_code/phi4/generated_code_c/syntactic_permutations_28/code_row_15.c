#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define MAX_URL_LENGTH 1024

int compile_regex(regex_t *re, const char *pattern) {
    int reti;
    if ((reti = regcomp(re, pattern, REG_EXTENDED)) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    return 0;
}

void free_resources(regex_t *re) {
    regfree(re);
}

int match_url(regex_t *re, const char *url) {
    int reti;
    regmatch_t pmatch[1];
    
    if ((reti = regexec(re, url, 1, pmatch, 0)) == REG_NOMATCH) {
        return 0; // URL does not match
    } else if (reti) {
        fprintf(stderr, "Regex match failed\n");
        exit(1);
    }
    
    return 1; // URL matches
}

const char* get_redirect_url(regex_t *re, const char *url) {
    if (match_url(re, url)) {
        return url;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    regex_t re;
    const char *pattern = "https?://.*\\.example\\.com/.*";

    if (compile_regex(&re, pattern) != 0) {
        return EXIT_FAILURE;
    }

    char url[MAX_URL_LENGTH];
    
    printf("Enter URL: ");
    if (!fgets(url, sizeof(url), stdin)) {
        fprintf(stderr, "Error reading input\n");
        free_resources(&re);
        return EXIT_FAILURE;
    }
    
    // Remove newline character
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[len - 1] = '\0';
    }

    const char *redirect_url = get_redirect_url(&re, url);
    printf("Redirecting to: %s\n", redirect_url);

    free_resources(&re);
    return EXIT_SUCCESS;
}