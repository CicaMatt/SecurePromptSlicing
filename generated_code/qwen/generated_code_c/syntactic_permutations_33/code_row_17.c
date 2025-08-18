#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    if (strstr(url, "http") != NULL || strstr(url, "https") != NULL) {
        printf("Location: %s\r\n\r\n", url);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Invalid URL format.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    // Simulating receiving a URL parameter, e.g., from a web server
    strcpy(url, "http://example.com"); // Change this to test different URLs
    
    redirect_invalid_url(url);
    
    return 0;
}