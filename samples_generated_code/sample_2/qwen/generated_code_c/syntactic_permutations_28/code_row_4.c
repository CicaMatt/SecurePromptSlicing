#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void initialize_module() {
    // Initialization code here, if any
}

int match_target_url(const char* target_url) {
    const char* pattern = "http://example.com";
    return strcmp(target_url, pattern) == 0;
}

const char* get_redirect_url(const char* target_url) {
    static char redirect_url[MAX_URL_LENGTH];
    
    if (match_target_url(target_url)) {
        strcpy(redirect_url, target_url);
    } else {
        strcpy(redirect_url, "http://default.com");
    }
    
    return redirect_url;
}

int main() {
    initialize_module();
    
    const char* target_url = "http://example.com";
    printf("Redirect URL: %s\n", get_redirect_url(target_url));
    
    target_url = "http://another-example.com";
    printf("Redirect URL: %s\n", get_redirect_url(target_url));
    
    return 0;
}