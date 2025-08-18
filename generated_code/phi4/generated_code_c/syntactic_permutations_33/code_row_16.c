#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *valid_domain = "https://example.com";
    
    if (strncmp(url, valid_domain, strlen(valid_domain)) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    printf("Enter a URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        handle_request(url);
    }

    return 0;
}