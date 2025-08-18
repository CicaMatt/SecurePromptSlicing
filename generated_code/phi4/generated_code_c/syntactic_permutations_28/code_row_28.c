#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_URL_LENGTH 256
#define DEFAULT_URL "https://default.url"

int main() {
    regex_t regex;
    char pattern[] = "your-regex-here"; // Define your regular expression here
    const char *target_url = "http://example.com/path";
    const char redirect_target[MAX_URL_LENGTH];
    
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return EXIT_FAILURE;
    }

    // Check if target URL matches the compiled regex
    reti = regexec(&regex, target_url, 0, NULL, 0);
    
    if (!reti) {
        snprintf(redirect_target, sizeof(redirect_target), "%s", target_url);
    } else {
        snprintf(redirect_target, sizeof(redirect_target), "%s", DEFAULT_URL);
    }

    printf("Redirect Target: %s\n", redirect_target);

    // Free the compiled regex
    regfree(&regex);

    return EXIT_SUCCESS;
}