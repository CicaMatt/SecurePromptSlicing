#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("Content-Length: 0\r\n");
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("Content-Length: 26\r\n");
        printf("\r\n");
        printf("Error: URL is not from example.com.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/redirect") != 0) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("Content-Length: 17\r\n");
        printf("\r\n");
        printf("Error: Route not found.\n");
        return 1;
    }

    char url[BUFFER_SIZE];
    snprintf(url, BUFFER_SIZE, "%s", argv[2]);

    redirect_invalid_url(url);

    return 0;
}