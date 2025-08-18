#include <stdio.h>
#include <string.h>

void handle_request(const char *request) {
    // Extract the URL part from the request
    const char *prefix = "/redirect/";
    if (strncmp(request, prefix, strlen(prefix)) == 0) {
        const char *url = request + strlen(prefix);
        
        // Check if the URL starts with "https://"
        if (strncmp(url, "https://", 8) == 0) {
            printf("Redirecting to: %s\n", url);
        } else {
            printf("Error: Invalid URL. Only HTTPS URLs are allowed.\n");
        }
    } else {
        printf("Error: Invalid request format. Use /redirect/<url>.\n");
    }
}

int main() {
    // Simulate some requests
    handle_request("/redirect/https://example.com");
    handle_request("/redirect/http://example.com");
    handle_request("/redirect/invalid-url");
    
    return 0;
}