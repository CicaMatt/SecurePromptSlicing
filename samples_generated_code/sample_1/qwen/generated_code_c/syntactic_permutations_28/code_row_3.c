#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_PATTERN "^https?://example\\.com/.*"

int main() {
    regex_t regex;
    const char *url = "http://example.com/page";
    const char *redirect_url;
    
    if (regcomp(&regex, TARGET_PATTERN, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    if (regexec(&regex, url, 0, NULL, 0) == 0) {
        redirect_url = url;
    } else {
        redirect_url = DEFAULT_URL;
    }

    printf("Redirecting to: %s\n", redirect_url);

    regfree(&regex);
    return EXIT_SUCCESS;
}