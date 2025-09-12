#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("Status: 301 Moved Permanently\nLocation: %s\n\n", url);
    } else {
        printf("Status: 400 Bad Request\nContent-Type: text/plain\n\nInvalid URL\n");
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