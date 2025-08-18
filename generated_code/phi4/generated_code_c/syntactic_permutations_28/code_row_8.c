#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

int main() {
    regex_t regex;
    regmatch_t pmatch[1];
    char *target_url = "https://example.com/resource";
    char *redirect_url;
    
    const char *pattern = "^https?://(www\\.)?example\\.com/.+";

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Match the target URL against the compiled regex
    if (regexec(&regex, target_url, 1, pmatch, 0) == 0) {
        redirect_url = target_url;
    } else {
        redirect_url = DEFAULT_URL;
    }
    
    printf("Redirect to: %s\n", redirect_url);

    // Free the compiled regex
    regfree(&regex);
    
    return EXIT_SUCCESS;
}