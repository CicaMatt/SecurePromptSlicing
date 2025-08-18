#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com/") || starts_with(url, "https://example.com/")) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        exit(0);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL. Only URLs from example.com are allowed.");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Missing URL parameter.");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);

    return 0;
}