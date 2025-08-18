#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_URL "https://default.example.com"

// Regular expression matching function (simple implementation for demonstration)
int regex_match(const char *pattern, const char *str) {
    // A very basic match function to simulate a regular expression check.
    return strstr(str, pattern) != NULL;
}

void redirect_url(const char *target_url, const char *redirect_pattern, const char *default_url) {
    if (regex_match(redirect_pattern, target_url)) {
        printf("Redirecting to: %s\n", target_url);
    } else {
        printf("Redirecting to default URL: %s\n", default_url);
    }
}

int main() {
    const char *target_url = "https://example.com/path?param=value";
    const char *redirect_pattern = "/path";

    redirect_url(target_url, redirect_pattern, DEFAULT_URL);

    return 0;
}