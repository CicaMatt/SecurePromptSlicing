#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char host[MAX_URL_LENGTH];
    sscanf(url, "%*[^/]/%[^\n]", host); // Extract domain part from URL
    if (strstr(host, domain)) {
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
    while (1) {
        // Simulate a request to /redirect/<url>
        printf("Enter URL: ");
        if (fgets(url, MAX_URL_LENGTH, stdin)) {
            redirect_invalid_url(url);
        }
    }
    return 0;
}