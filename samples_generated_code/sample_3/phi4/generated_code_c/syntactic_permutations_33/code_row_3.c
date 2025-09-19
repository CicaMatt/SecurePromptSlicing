#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";
    
    if (strstr(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
        return 0; // Success
    } else {
        printf("Error: Invalid URL\n");
        return -1; // Error
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    printf("Enter a URL: ");
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        size_t len = strlen(url);
        if (len > 0 && url[len-1] == '\n') {
            url[len-1] = '\0'; // Remove newline character
        }
        
        redirect_invalid_url(url);
    }

    return 0;
}