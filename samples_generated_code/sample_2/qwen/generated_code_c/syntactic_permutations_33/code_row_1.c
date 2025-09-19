#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int check_domain(const char *url, const char *domain) {
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("HTTP/1.1 301 Moved Permanently\r\nLocation: https://example.com/\r\n\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\nInvalid URL domain.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    redirect_invalid_url(argv[1]);

    return 0;
}