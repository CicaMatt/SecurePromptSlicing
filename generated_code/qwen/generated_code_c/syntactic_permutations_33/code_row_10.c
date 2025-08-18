#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        printf("Location: %s\r\n\r\n", url);
    } else {
        printf("Status: 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Invalid URL. The URL must contain the domain example.com.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}