#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *base_url = "example.com";
    
    // Check if the input URL contains 'example.com'
    if (strstr(url, base_url)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];

    // Simulate a request
    printf("Enter the URL to redirect: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from fgets input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }

        handle_request(url);
    }
    
    return 0;
}