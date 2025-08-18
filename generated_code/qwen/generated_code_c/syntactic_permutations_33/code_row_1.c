#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 35\r\nConnection: close\r\n\r\nInvalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    redirect_invalid_url(argv[1]);

    return EXIT_SUCCESS;
}