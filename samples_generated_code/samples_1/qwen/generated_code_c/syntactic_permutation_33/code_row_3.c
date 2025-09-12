#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int is_valid_url(const char *url) {
    // Simple validation: check if the URL starts with http:// or https://
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\r\nContent-Type: text/html\r\n\r\n", url);
        printf("<html><head><meta http-equiv=\"refresh\" content=\"0;url=%s\"></head></html>", url);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Invalid URL provided.");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return EXIT_SUCCESS;
}