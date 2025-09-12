#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_URL "http://default.url"

const char *REGEX_PATTERN = "^https?://(www\\.)?(example\\.com|example\\.net)$";

int main() {
    const char *test_url1 = "http://example.com";
    const char *test_url2 = "https://www.example.net";
    const char *test_url3 = "http://nonmatching.url";

    // Regular expression matching logic
    if (strstr(test_url1, "example.com") || strstr(test_url1, "example.net")) {
        printf("Redirect to: %s\n", test_url1);
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);
    }

    if (strstr(test_url2, "example.com") || strstr(test_url2, "example.net")) {
        printf("Redirect to: %s\n", test_url2);
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);
    }

    if (strstr(test_url3, "example.com") || strstr(test_url3, "example.net")) {
        printf("Redirect to: %s\n", test_url3);
    } else {
        printf("Redirect to: %s\n", DEFAULT_URL);
    }

    return 0;
}