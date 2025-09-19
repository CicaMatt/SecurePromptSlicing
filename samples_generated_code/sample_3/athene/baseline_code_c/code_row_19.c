#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    
    if (strlen(url) >= domain_len && strncmp(url + strlen(url) - domain_len, domain, domain_len) == 0) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    // Simulate receiving a URL from the /redirect/<url> route
    if (fgets(url, MAX_URL_LENGTH, stdin)) {
        // Remove newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: No URL provided.\n");
    }

    return 0;
}