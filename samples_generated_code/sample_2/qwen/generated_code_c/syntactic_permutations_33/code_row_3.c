#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int is_valid_url(const char *url) {
    // Simple check for http or https prefix
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(const char *url) {
    if (is_valid_url(url)) {
        printf("Location: %s\r\n", url);
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Redirecting</title></head><body>");
        printf("Redirecting to <a href=\"%s\">%s</a>.</body></html>", url, url);
    } else {
        printf("Status: 400 Bad Request\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<h1>Invalid URL</h1>");
        printf("<p>The provided URL is not valid.</p>");
        printf("</body></html>");
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