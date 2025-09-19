#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void handle_request(const char *path) {
    const char *url_start = strstr(path, "/redirect/");
    if (url_start != NULL) {
        url_start += strlen("/redirect/");
        char url[BUFFER_SIZE];
        strncpy(url, url_start, sizeof(url) - 1);
        url[sizeof(url) - 1] = '\0';

        redirect_invalid_url(url);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\nNot Found");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Length: 18\r\n\r\nInvalid URL");
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), stdin);

    handle_request(buffer);

    return 0;
}