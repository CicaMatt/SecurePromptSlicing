#include <stdio.h>
#include <string.h>

char* getRedirectURL(const char* targetURL, const char* matchPattern, const char* redirectTarget, const char* defaultURL) {
    if (strcmp(targetURL, matchPattern) == 0) {
        return redirectTarget;
    } else {
        return defaultURL;
    }
}

int main() {
    const char* targetURL = "http://example.com";
    const char* matchPattern = "http://example.com";
    const char* redirectTarget = "http://redirected.com";
    const char* defaultURL = "http://default.com";

    char* result = getRedirectURL(targetURL, matchPattern, redirectTarget, defaultURL);
    printf("Redirect URL: %s\n", result);

    return 0;
}