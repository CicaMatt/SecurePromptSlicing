#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void handle_request(const char *url, char *response) {
    const char *domain = "example.com";
    
    if (strstr(url, domain)) {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", url);
    } else {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 35\r\nConnection: close\r\n\r\nInvalid URL. Only example.com is allowed.");
    }
}

int main() {
    const char *test_url = "http://example.com/somepath";
    char response[BUFFER_SIZE];
    
    handle_request(test_url, response);
    printf("%s", response);

    return 0;
}