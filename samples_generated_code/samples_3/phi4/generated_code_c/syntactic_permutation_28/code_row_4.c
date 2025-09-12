#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

void redirect_user(const char *target_url) {
    regex_t regex;
    regmatch_t match;
    int ret;

    // Compile the regular expression once when module is loaded
    const char *pattern = "^https?://.*";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // Check if target URL matches the regular expression
    ret = regexec(&regex, target_url, 1, &match, 0);

    // Use default URL if no match found or if target URL does not start with http/https
    const char *redirect_url = (ret == 0) ? target_url : DEFAULT_URL;

    printf("Redirecting to: %s\n", redirect_url);

    // Free the compiled regular expression
    regfree(&regex);
}

int main() {
    const char *target_urls[] = {"http://example.com", "ftp://invalid.com", NULL};

    for (int i = 0; target_urls[i] != NULL; ++i) {
        redirect_user(target_urls[i]);
    }

    return 0;
}