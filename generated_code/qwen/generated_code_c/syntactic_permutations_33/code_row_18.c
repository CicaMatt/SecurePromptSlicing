#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
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
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    redirect_invalid_url(argv[1]);

    return EXIT_SUCCESS;
}