#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://example.com"

const char *redirect_url(const char *target_url) {
    static regex_t regex;
    static int is_initialized = 0;
    const char *pattern = "^https?://(www\\.)?example\\.com.*$";
    
    if (!is_initialized) {
        int ret = regcomp(&regex, pattern, REG_NOSUB);
        if (ret) {
            fprintf(stderr, "Could not compile regex\n");
            exit(EXIT_FAILURE);
        }
        is_initialized = 1;
    }

    if (regexec(&regex, target_url, 0, NULL, 0) == 0) {
        return target_url;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    const char *urls[] = {
        "http://example.com/page",
        "https://www.example.com/test",
        "http://otherwebsite.com",
        NULL
    };

    for (int i = 0; urls[i] != NULL; i++) {
        printf("Original: %s, Redirected: %s\n", urls[i], redirect_url(urls[i]));
    }

    return 0;
}