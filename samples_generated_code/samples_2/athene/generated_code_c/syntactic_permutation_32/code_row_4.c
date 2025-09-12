#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    char host[MAX_URL_LENGTH];
    sscanf(url, "%*[^/]/%[^\n]", host); // Extract the domain part of URL
    if (strstr(host, domain)) {
        printf("Location: https://example.com/\r\n");
        printf("Content-Type: text/html\r\n\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid URL: %s\n", url);
    }
}

int main() {
    const char *test_url = "http://example.com/somepath";
    redirect_invalid_url(test_url);
    return 0;
}