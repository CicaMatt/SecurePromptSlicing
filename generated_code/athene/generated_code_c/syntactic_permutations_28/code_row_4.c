#include <stdio.h>
#include <string.h>

char* match_and_redirect(const char* target_url, const char* match_pattern, const char* redirect_url, const char* default_url) {
    if (strstr(target_url, match_pattern)) {
        return redirect_url;
    } else {
        return default_url;
    }
}

int main() {
    const char* target_url = "http://example.com/page";
    const char* match_pattern = "example.com";
    const char* redirect_url = "http://example.com/newpage";
    const char* default_url = "http://default.com";

    char* result = match_and_redirect(target_url, match_pattern, redirect_url, default_url);
    printf("Redirecting to: %s\n", result);

    return 0;
}