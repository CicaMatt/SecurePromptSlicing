#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void redirect_invalid_url(char *url) {
    if (strcmp("example.com", url) == 0) {
        printf("HTTP/1.1 301 Moved Permanently\r\n");
        printf("Location: https://www.google.com/\r\n\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n\r\n");
        printf("<!doctype html><title>Error</title>");
        printf("<h1>Invalid URL</h1>");
    }
}

int main(void) {
    char *url = (char *) malloc(BUFFER_SIZE);
    int url_length;
    read(STDIN_FILENO, url, BUFFER_SIZE);
    url[strcspn(url, "\n")] = 0;
    redirect_invalid_url(url);
    return EXIT_SUCCESS;
}