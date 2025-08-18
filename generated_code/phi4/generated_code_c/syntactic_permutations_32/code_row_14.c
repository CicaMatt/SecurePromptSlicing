#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\n");
    printf("Location: %s\n\n", url);
}

void handle_request(const char *request_url) {
    const char *redirect_prefix = "/redirect/";
    if (strncmp(request_url, redirect_prefix, strlen(redirect_prefix)) == 0) {
        const char *url_to_redirect = request_url + strlen(redirect_prefix);

        // Simple validation: Check if URL starts with "http://" or "https://"
        if ((strncmp(url_to_redirect, "http://", 7) == 0) || (strncmp(url_to_redirect, "https://", 8) == 0)) {
            redirect(url_to_redirect);
        } else {
            printf("HTTP/1.1 400 Bad Request\n");
            printf("Content-Type: text/plain\n\n");
            printf("Invalid URL.\n");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n\n");
        printf("Route not found.\n");
    }
}

int main() {
    char request_url[MAX_URL_LENGTH];

    // Simulate receiving a request
    printf("Enter the request URL: ");
    fgets(request_url, MAX_URL_LENGTH, stdin);

    // Remove newline character if present
    size_t len = strlen(request_url);
    if (len > 0 && request_url[len - 1] == '\n') {
        request_url[--len] = '\0';
    }

    handle_request(request_url);

    return 0;
}