#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

typedef struct {
    const char *path;
    void (*handler)(char *url);
} Route;

void redirect_invalid_url(char *url) {
    if (strncmp(url, "http://example.com", 19) == 0 || 
        strncmp(url, "https://example.com", 20) == 0) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid URL");
    }
}

void handle_request(char *request) {
    char method[10], path[MAX_URL_LENGTH];
    sscanf(request, "%s %s", method, path);

    if (strcmp(method, "GET") == 0 && strncmp(path, "/redirect/", 10) == 0) {
        char url[MAX_URL_LENGTH];
        strcpy(url, path + 10);
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
    }
}

int main() {
    char request[MAX_URL_LENGTH] = "GET /redirect/http://example.com/path HTTP/1.1";
    handle_request(request);
    return 0;
}