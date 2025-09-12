#include <stdio.h>
#include <string.h>

const char* default_url = "http://example.com/default";

int url_matches(const char* target, const char* pattern) {
    return strcmp(target, pattern) == 0;
}

void perform_redirect(const char* incoming_url) {
    const char* match_url = "http://example.com/special";
    const char* redirect_target = (url_matches(incoming_url, "/special-path") ? match_url : default_url);
    
    printf("Redirecting to: %s\n", redirect_target);
}

int main() {
    const char* incoming_urls[] = {"/home", "/about", "/special-path", "/contact"};
    int num_urls = sizeof(incoming_urls) / sizeof(incoming_urls[0]);

    for (int i = 0; i < num_urls; ++i) {
        perform_redirect(incoming_urls[i]);
    }

    return 0;
}