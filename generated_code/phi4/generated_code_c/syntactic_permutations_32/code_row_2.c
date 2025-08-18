#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request) {
    char method[BUFFER_SIZE];
    char path[BUFFER_SIZE];

    sscanf(request, "%s %s", method, path);

    if (strcmp(method, "GET") == 0 && strncmp(path, "/redirect/", 10) == 0) {
        char url[BUFFER_SIZE] = {0};
        strcpy(url, path + 10);
        
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Not found\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com")) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: http://%s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid URL: %s\n", url);
    }
}

int main() {
    char request[BUFFER_SIZE] = {0};

    // Simulating a web server receiving a GET request
    printf("Enter the HTTP request (e.g., 'GET /redirect/http://example.com/test'): ");
    fgets(request, BUFFER_SIZE, stdin);

    handle_request(request);
    
    return 0;
}