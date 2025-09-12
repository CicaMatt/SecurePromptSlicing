#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char *pos;

    if ((pos = strstr(url, domain)) != NULL && (pos == url || *(pos - 1) == '.')) {
        printf("HTTP/1.1 302 Found\r\nLocation: /\r\nConnection: close\r\n\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nInvalid URL");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}