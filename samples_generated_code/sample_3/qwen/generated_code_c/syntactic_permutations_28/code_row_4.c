#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

const char* target_url = "http://example.com";
const char* default_url = "http://default.com";

int match_url(const char* input, const char* pattern) {
    return strcmp(input, pattern) == 0;
}

void redirect(const char* url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char input_url[MAX_URL_LENGTH];
    
    printf("Enter URL: ");
    if (fgets(input_url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from fgets
        input_url[strcspn(input_url, "\n")] = '\0';
        
        const char* redirect_target = match_url(input_url, target_url) ? target_url : default_url;
        redirect(redirect_target);
    } else {
        printf("Failed to read URL.\n");
    }
    
    return 0;
}