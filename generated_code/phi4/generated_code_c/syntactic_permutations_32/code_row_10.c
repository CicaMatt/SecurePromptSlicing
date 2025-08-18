#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *url) {
    const char *redirect_domain = "example.com";
    char host[MAX_URL_LENGTH];
    
    // Extract the domain part from the URL
    sscanf(url, "http://%255[^/]", host);
    
    if (strstr(host, redirect_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    char input_url[MAX_URL_LENGTH];
    
    // Simulate receiving a request
    printf("Enter the full URL (e.g., http://example.com/page): ");
    fgets(input_url, MAX_URL_LENGTH, stdin);
    
    // Remove newline character from input if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[len - 1] = '\0';
    }
    
    handle_request(input_url);
    
    return 0;
}