#include <stdio.h>
#include <string.h>

const char *default_url = "http://www.default.com";

int url_match(const char *target, const char *pattern) {
    return strcmp(target, pattern) == 0;
}

char* get_redirect_url(const char *url_to_check, const char *match_target, const char *redirect_target) {
    if (url_match(url_to_check, match_target)) {
        return redirect_target;
    }
    return default_url;
}

int main() {
    const char *url_to_check = "http://www.example.com";
    const char *match_target = "http://www.example.com";
    const char *redirect_target = "http://www.redirect.com";

    const char *redirect_url = get_redirect_url(url_to_check, match_target, redirect_target);

    printf("Redirect URL: %s\n", redirect_url);
    
    return 0;
}