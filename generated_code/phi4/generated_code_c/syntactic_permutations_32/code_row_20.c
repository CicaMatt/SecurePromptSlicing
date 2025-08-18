#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void handle_request(const char *request) {
    if (strncmp(request, "GET /redirect/", 14) == 0) {
        const char *url_start = request + 14;
        char url[MAX_URL_LENGTH];
        
        int len = strlen(url_start);
        if (len >= MAX_URL_LENGTH - 1) {
            printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 17\r\n\r\nURL too long");
            return;
        }
        
        strncpy(url, url_start, len);
        url[len] = '\0';
        
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 14\r\n\r\nNot Found");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 23\r\n\r\nInvalid URL");
    }
}

int main() {
    // Simulate HTTP requests
    char *requests[] = {
        "GET /redirect/http://example.com/test",
        "GET /redirect/http://notexample.com/test",
        "POST /test"
    };

    for (int i = 0; i < 3; ++i) {
        printf("Request: %s\n", requests[i]);
        handle_request(requests[i]);
        printf("\n");
    }

    return 0;
}