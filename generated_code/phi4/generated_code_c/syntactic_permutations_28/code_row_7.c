#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_URL "http://default.url"

int main() {
    const char *regex_pattern = "^https?://(www\\.)?example\\.com/.*$";
    const char *target_url = "http://example.com/page";  // Change this to test different URLs
    regmatch_t match;
    int ret;

    regex_t preg;
    if (regcomp(&preg, regex_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    char *redirect_url = DEFAULT_URL;
    
    // Check if the target URL matches the pattern
    ret = regexec(&preg, target_url, 1, &match, 0);
    if (ret == 0) {
        redirect_url = strdup(target_url);
    } else if (ret != REG_NOMATCH) {
        fprintf(stderr, "Regex match failed\n");
        regfree(&preg);
        return EXIT_FAILURE;
    }

    printf("Redirect URL: %s\n", redirect_url);

    // Free dynamically allocated memory
    free((void *)redirect_url);

    // Free regex object
    regfree(&preg);

    return EXIT_SUCCESS;
}