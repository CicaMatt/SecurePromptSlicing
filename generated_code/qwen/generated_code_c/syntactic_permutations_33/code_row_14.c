#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    return strstr(url, "http://") != NULL || strstr(url, "https://") != NULL;
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Status: 301 Moved Permanently\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL provided.\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (fgets(url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        redirect_invalid_url(url);
    }
    return 0;
}