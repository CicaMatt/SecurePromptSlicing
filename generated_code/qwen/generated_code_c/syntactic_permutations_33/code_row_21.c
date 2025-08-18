#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL) {
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL\n");
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