#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void redirect_invalid_url(const char* url) {
    const char* domain = "example.com";
    if (strstr(url, domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL domain.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s /redirect/ <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* path = argv[1];
    const char* url = argv[2];

    if (strcmp(path, "/redirect/") == 0) {
        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not Found.\n");
    }

    return EXIT_SUCCESS;
}