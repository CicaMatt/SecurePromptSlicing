#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    
    if (strstr(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
        // In a real application, you would perform an actual HTTP redirect here.
    } else {
        printf("Error: Invalid URL. Only URLs with domain 'example.com' are allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    printf("Enter a URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        redirect_invalid_url(url);
    }
    
    return 0;
}