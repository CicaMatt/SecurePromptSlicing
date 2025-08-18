#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 36\r\nConnection: close\r\n\r\nInvalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char url[MAX_URL_LENGTH];
    strncpy(url, argv[1], MAX_URL_LENGTH);
    url[MAX_URL_LENGTH - 1] = '\0';

    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}