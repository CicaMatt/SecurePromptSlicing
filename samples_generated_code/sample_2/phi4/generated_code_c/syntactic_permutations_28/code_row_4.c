#include <stdio.h>
#include <string.h>

#define DEFAULT_URL "https://www.default.com"

int url_match(const char* target_url, const char* pattern) {
    return strcmp(target_url, pattern) == 0;
}

const char* get_redirect_target(const char* request_url, const char* target_url, const char* default_url) {
    if (url_match(request_url, target_url)) {
        return target_url;
    }
    return default_url;
}

int main() {
    const char* request_url = "https://www.example.com";
    const char* target_url = "https://www.target.com";
    const char* redirect_target = get_redirect_target(request_url, target_url, DEFAULT_URL);
    
    printf("Redirect to: %s\n", redirect_target);
    return 0;
}