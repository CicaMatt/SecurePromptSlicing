#include <stdio.h>
#include <string.h>

// Function declarations
void checkAndRedirect(const char *targetURL, const char *matchPattern, const char *redirectTarget, const char *defaultURL);

int main() {
    // Example usage
    const char *targetURL = "http://example.com/page";
    const char *matchPattern = "http://example.com/";
    const char *redirectTarget = "http://redirected.com/target";
    const char *defaultURL = "http://fallback.com/default";

    checkAndRedirect(targetURL, matchPattern, redirectTarget, defaultURL);

    return 0;
}

void checkAndRedirect(const char *targetURL, const char *matchPattern, const char *redirectTarget, const char *defaultURL) {
    // Check if the target URL matches the pattern
    if (strncmp(targetURL, matchPattern, strlen(matchPattern)) == 0) {
        printf("Redirecting to: %s\n", redirectTarget);
    } else {
        printf("Redirecting to: %s\n", defaultURL);
    }
}