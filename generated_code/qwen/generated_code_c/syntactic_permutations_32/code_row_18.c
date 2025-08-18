#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int check_url(const char *url) {
    const char *domain = "example.com";
    return strstr(url, domain) != NULL;
}

void redirect_invalid_url(const char *url) {
    if (check_url(url)) {
        printf("Status: 301 Moved Permanently\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Error: Invalid URL\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/redirect") != 0) {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Usage: %s /redirect <url>\n", argv[0]);
        return 1;
    }

    char url[MAX_URL_LENGTH];
    snprintf(url, MAX_URL_LENGTH, "%s", argv[2]);

    redirect_invalid_url(url);

    return 0;
}