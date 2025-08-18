#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    // Simple check for a valid URL starting with http:// or https://
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Status: 302 Moved Temporarily\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL\r\n");
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