#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(const char *url, char *response) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 301 Moved Permanently\r\nLocation: http://%s/\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", domain);
    } else {
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 28\r\nConnection: close\r\n\r\nInvalid URL - must contain example.com");
    }
}

int main() {
    const char *url = "http://example.com/test";
    char response[BUFFER_SIZE];
    
    redirect_invalid_url(url, response);
    printf("%s", response);

    return 0;
}