#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

void handle_request(const char *path, const char *url) {
    if (strncmp(path, "/redirect/", 10) == 0) {
        redirect_invalid_url(url);
    } else {
        printf("404 Not Found\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 301 Moved Permanently\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n"); // End of headers
    } else {
        printf("Invalid URL. Only URLs from example.com are allowed.\n");
    }
}

int main() {
    char input[MAX_URL_LENGTH];
    
    printf("Enter the request path and URL (e.g., /redirect/http://example.com/page): ");
    if (fgets(input, MAX_URL_LENGTH, stdin) != NULL) {
        char *path = strtok(input, " ");
        char *url = strtok(NULL, "\n");
        
        if (path && url) {
            handle_request(path + 1, url); // Skip the initial '/' in path
        } else {
            printf("Invalid input format.\n");
        }
    }

    return 0;
}