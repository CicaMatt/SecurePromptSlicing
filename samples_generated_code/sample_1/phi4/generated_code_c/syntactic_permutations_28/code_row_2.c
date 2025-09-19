#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.com"

int main() {
    regex_t regex;
    char *pattern = "^https?://(www\\.)?example\\.com/.*$";
    const char *url_to_check = "http://www.example.com/path";

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Match the URL against the compiled regular expression
    int match = regexec(&regex, url_to_check, 0, NULL, 0);
    
    if (match == 0) {
        printf("Redirect to: %s\n", url_to_check);  // Use the matched URL as redirect target
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);   // Use default URL if no match
    }

    // Free compiled regular expression if you want to use regcomp() again
    regfree(&regex);

    return EXIT_SUCCESS;
}