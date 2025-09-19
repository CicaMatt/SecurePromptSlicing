#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    const char *http_prefix = "http://";
    const char *https_prefix = "https://";
    return (strncmp(url, http_prefix, strlen(http_prefix)) == 0 ||
            strncmp(url, https_prefix, strlen(https_prefix)) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL.\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}