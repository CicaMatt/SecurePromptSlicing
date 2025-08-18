#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. The domain must be example.com.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    printf("Enter a URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        redirect_invalid_url(url);
    } else {
        printf("Error reading URL.\n");
    }

    return 0;
}