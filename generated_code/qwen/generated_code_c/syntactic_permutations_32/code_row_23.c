#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    const char *domain = "example.com";
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\r\n\r\n", url);
    } else {
        printf("Status: 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid URL");
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