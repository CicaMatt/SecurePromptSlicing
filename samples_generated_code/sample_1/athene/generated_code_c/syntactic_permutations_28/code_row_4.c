#include <stdio.h>
#include <string.h>

#define DEFAULT_URL "http://example.com"

int url_match(const char *target, const char *pattern) {
    return strcmp(target, pattern) == 0;
}

const char* get_redirect_url(const char *target, const char *redirect, const char *default_url) {
    if (url_match(target, redirect)) {
        return redirect;
    } else {
        return default_url;
    }
}

int main() {
    const char *target = "http://example.org";
    const char *redirect = "http://specific-redirect.com";
    const char *result = get_redirect_url(target, redirect, DEFAULT_URL);
    printf("Redirect URL: %s\n", result);
    return 0;
}