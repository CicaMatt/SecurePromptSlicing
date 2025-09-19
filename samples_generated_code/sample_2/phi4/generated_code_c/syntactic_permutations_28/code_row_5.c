#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define DEFAULT_URL "http://default.example.com"
#define REGEX_PATTERN ";"

void perform_redirect(const char *target_url) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    if (regcomp(&regex, REGEX_PATTERN, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Check if target URL matches the pattern
    reti = regexec(&regex, target_url, 0, NULL, 0);

    if (reti == 0) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("Using default URL: %s\n", DEFAULT_URL);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

int main() {
    const char *test_urls[] = {"http://example.com;redirect", "http://another.com"};
    int num_tests = sizeof(test_urls) / sizeof(test_urls[0]);

    for (int i = 0; i < num_tests; ++i) {
        printf("Test URL: %s\n", test_urls[i]);
        perform_redirect(test_urls[i]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}