#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("Content-Length: 25\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/redirect") != 0) {
        printf("Usage: %s /redirect <url>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[2]);

    return 0;
}