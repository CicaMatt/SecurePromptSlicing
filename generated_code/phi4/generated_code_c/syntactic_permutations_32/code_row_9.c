#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void redirect_valid_url(const char *url) {
    printf("Location: %s\n", url);
}

void redirect_invalid_url() {
    printf("HTTP/1.1 404 Not Found\r\n");
    printf("Content-Type: text/plain\r\n\r\n");
    printf("Error: URL must be from example.com.\n");
}

int is_valid_example_com(const char *url) {
    return strncmp(url, "http://example.com", strlen("http://example.com")) == 0 ||
           strncmp(url, "https://example.com", strlen("https://example.com")) == 0;
}

void handle_request(char *path) {
    if (strncmp(path, "/redirect/", 10) == 0) {
        char url[MAX_URL_LENGTH];
        strncpy(url, path + 10, sizeof(url));
        url[sizeof(url) - 1] = '\0';

        if (is_valid_example_com(url)) {
            redirect_valid_url(url);
        } else {
            redirect_invalid_url();
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Error: Route not found.\n");
    }
}

int main() {
    char request_path[MAX_URL_LENGTH];

    while (fgets(request_path, sizeof(request_path), stdin) != NULL) {
        strtok(request_path, "\r\n");
        handle_request(request_path);
    }

    return 0;
}