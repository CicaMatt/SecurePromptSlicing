#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

int validate_url(const char *url) {
    // Simple validation: check if the URL starts with "http://" or "https://"
    return (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0);
}

void redirect_invalid_url(const char *url) {
    if (validate_url(url)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><head></head><body>Redirecting...</body></html>");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Invalid URL.");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    if (getenv("QUERY_STRING") != NULL) {
        sscanf(getenv("QUERY_STRING"), "url=%1023s", url);
        redirect_invalid_url(url);
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("No URL provided.");
    }
    return 0;
}