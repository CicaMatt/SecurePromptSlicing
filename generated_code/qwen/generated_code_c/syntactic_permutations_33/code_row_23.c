#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /\r\n");
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL domain.\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}