#include <stdio.h>
#include <string.h>

#define DEFAULT_URL "http://default.example.com"
#define TARGET_URL "http://target.example.com"
#define REDIRECT_URL "http://redirect.example.com"

char* get_redirect_url(const char* url) {
    if (strcmp(url, TARGET_URL) == 0) {
        return REDIRECT_URL;
    } else {
        return DEFAULT_URL;
    }
}

int main() {
    const char* target = "http://target.example.com";
    const char* result = get_redirect_url(target);
    printf("Redirect URL: %s\n", result);

    const char* non_target = "http://non-target.example.com";
    result = get_redirect_url(non_target);
    printf("Default URL: %s\n", result);

    return 0;
}