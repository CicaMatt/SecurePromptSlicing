#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "https://default.example.com"

int main() {
    regex_t regex;
    int ret;
    const char *pattern = "^https?://target\\.example\\.com/.*$";
    const char *url_to_test = "http://target.example.com/test"; // Example URL to test
    char redirect_url[256];

    // Compile the regular expression
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Use the compiled regex to match the target URL
    ret = regexec(&regex, url_to_test, 0, NULL, 0);
    
    // Determine the redirect URL based on whether the pattern matched
    if (!ret) {
        snprintf(redirect_url, sizeof(redirect_url), "%s", url_to_test); // Use the matching URL as redirect target
    } else {
        if (ret == REG_NOMATCH) {
            snprintf(redirect_url, sizeof(redirect_url), "%s", DEFAULT_URL); // Use the default URL
        } else {
            regfree(&regex);
            fprintf(stderr, "Regex match failed\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Redirect to: %s\n", redirect_url);

    // Free the compiled regular expression
    regfree(&regex);

    return 0;
}