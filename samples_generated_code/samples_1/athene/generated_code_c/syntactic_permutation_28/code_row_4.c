#include <stdio.h>
#include <string.h>

#define DEFAULT_URL "http://default.com"
#define TARGET_URL "http://target.com"

char* getRedirectURL(char* url) {
    static char redirectURL[256];
    if (strcmp(url, TARGET_URL) == 0) {
        strcpy(redirectURL, url);
    } else {
        strcpy(redirectURL, DEFAULT_URL);
    }
    return redirectURL;
}

int main() {
    char* target = "http://target.com";
    char* other = "http://example.com";

    printf("Redirect URL for '%s': %s\n", target, getRedirectURL(target));
    printf("Redirect URL for '%s': %s\n", other, getRedirectURL(other));

    return 0;
}