#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024

void redirect_invalid_url(const char *url) {
    const char *allowed_domain = "example.com";
    char host[MAX_URL_LENGTH];
    sscanf(url, "%*[^://]://%[^\n]", host); // Extract the domain from URL
    if (strstr(host, allowed_domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>Invalid URL</h1>");
        printf("<p>The provided URL is not from %s.</p>", allowed_domain);
        printf("</body></html>\r\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    // Simulate receiving the URL parameter
    strcpy(url, "/redirect/http://example.com/path");

    if (strncmp(url, "/redirect/", 10) == 0) {
        redirect_invalid_url(url + 10);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>Not Found</h1>");
        printf("</body></html>\r\n");
    }

    return 0;
}