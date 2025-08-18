#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    const char *domain = "example.com";
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Status: 301 Moved Permanently\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Status: 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL.\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/redirect") != 0) {
        printf("Status: 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Route not found.\r\n");
        return 1;
    }

    char *url = argv[2];
    if (strlen(url) > MAX_URL_LENGTH) {
        printf("Status: 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: URL too long.\r\n");
        return 1;
    }

    redirect_invalid_url(url);
    return 0;
}