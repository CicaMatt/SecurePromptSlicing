#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 2048

bool is_valid_url(const char *url) {
    // Simple validation: check if the URL starts with "http://" or "https://"
    const char http[] = "http://";
    const char https[] = "https://";
    return (strncmp(url, http, strlen(http)) == 0 || strncmp(url, https, strlen(https)) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Content-Type: text/plain\n\n");
        printf("Error: No URL provided.\n");
        return 1;
    }

    const char *url = argv[1];
    redirect_invalid_url(url);
    return 0;
}