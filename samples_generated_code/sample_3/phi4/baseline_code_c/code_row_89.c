#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int compile_regex(regex_t *re, const char *pattern) {
    int reti;
    reti = regcomp(re, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }
    return 0;
}

const char* get_redirect_url(regex_t *re, const char *url, const char *default_url) {
    int reti;
    regmatch_t match;

    reti = regexec(re, url, 1, &match, 0);
    if (!reti) {
        return (char *)url; // If matches, use the target URL
    } else if (reti == REG_NOMATCH) {
        return default_url;
    } else {
        char msgbuf[100];
        regerror(reti, re, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return default_url;
    }
}

int main() {
    regex_t re;
    const char *pattern = "^https?://(www\\.)?.+\\.example\\.com/.*$";
    
    if (compile_regex(&re, pattern)) {
        exit(EXIT_FAILURE);
    }

    // Test URLs
    const char *urls[] = {
        "http://www.example.com/page1",
        "https://example.org/page2",
        "http://example.com/test",
        NULL
    };

    for (int i = 0; urls[i] != NULL; ++i) {
        const char *redirect_url = get_redirect_url(&re, urls[i], DEFAULT_URL);
        printf("Original URL: %s\nRedirect to: %s\n\n", urls[i], redirect_url);
    }

    regfree(&re);
    return 0;
}