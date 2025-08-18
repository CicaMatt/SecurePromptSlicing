#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

typedef struct {
    char url[MAX_URL_LENGTH];
} Request;

int redirect_invalid_url(Request *req) {
    if (strncmp(req->url, "http://example.com", strlen("http://example.com")) == 0 ||
        strncmp(req->url, "https://example.com", strlen("https://example.com")) == 0) {
        printf("Redirecting to: %s\n", req->url);
        return 1;
    }
    printf("Error: URL is not from example.com\n");
    return 0;
}

void handle_request(char *path) {
    if (strncmp(path, "/redirect/", strlen("/redirect/")) == 0) {
        Request req;
        strncpy(req.url, path + strlen("/redirect/"), MAX_URL_LENGTH - 1);
        req.url[MAX_URL_LENGTH - 1] = '\0';
        
        redirect_invalid_url(&req);
    } else {
        printf("Error: Invalid route\n");
    }
}

int main() {
    char input[MAX_URL_LENGTH];
    
    while (1) {
        printf("Enter URL path: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Remove newline character from input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        handle_request(input);
    }
    
    return 0;
}