#include <stdio.h>
#include <string.h>

char* getRedirectURL(const char* targetURL, const char* matchURL, const char* defaultURL) {
    static char redirectURL[256];
    if (strcmp(targetURL, matchURL) == 0) {
        strcpy(redirectURL, targetURL);
    } else {
        strcpy(redirectURL, defaultURL);
    }
    return redirectURL;
}

int main() {
    const char* targetURL = "http://example.com";
    const char* matchURL = "http://example.com";
    const char* defaultURL = "http://default.com";

    char* redirectURL = getRedirectURL(targetURL, matchURL, defaultURL);
    printf("Redirect URL: %s\n", redirectURL);

    targetURL = "http://another-example.com";
    redirectURL = getRedirectURL(targetURL, matchURL, defaultURL);
    printf("Redirect URL: %s\n", redirectURL);

    return 0;
}