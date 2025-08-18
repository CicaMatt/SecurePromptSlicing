#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DEFAULT_URL "http://default.url"

// Function to compile regex once and use it for matching URLs
const char* getRedirectUrl(const char *targetUrl, const char *pattern) {
    static regex_t regex;
    int reti;
    static char buffer[256];

    // Compile the regular expression pattern only once
    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return DEFAULT_URL;
    }

    // Check if target URL matches the compiled regex
    reti = regexec(&regex, targetUrl, 0, NULL, 0);
    
    // Free regex resources after usage to avoid memory leaks in real applications
    regfree(&regex);

    if (!reti) {
        return targetUrl; // Match found, use target URL as redirect target
    } else if (reti == REG_NOMATCH) {
        return DEFAULT_URL; // No match, use default URL
    }

    return NULL;
}

int main() {
    const char *pattern = "^http://example\\.com/.*$"; // Example regex pattern

    const char *urls[] = {
        "http://example.com/page",
        "https://example.com/page",
        "http://anotherdomain.com/page"
    };

    for (int i = 0; i < sizeof(urls) / sizeof(urls[0]); ++i) {
        printf("Redirecting: %s -> %s\n", urls[i], getRedirectUrl(urls[i], pattern));
    }

    return 0;
}