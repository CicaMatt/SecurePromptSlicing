#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int validate_url(const char *url) {
    if (url == NULL || strlen(url) > MAX_URL_LENGTH) return 0;
    // Simple check for http or https prefix
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) return 0;
    return 1;
}

void redirect_invalid_url(const char *url) {
    if (validate_url(url)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Missing URL parameter\n");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);
    return 0;
}