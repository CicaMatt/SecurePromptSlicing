#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    const char *path;
    void (*handler)(const char *url);
} Route;

bool starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

void redirect_invalid_url(const char *url) {
    if (starts_with(url, "http://example.com") || starts_with(url, "https://example.com")) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL. Only URLs from example.com are allowed.\r\n");
    }
}

void handle_request(const char *path, const char *query) {
    if (strncmp(path, "/redirect/", 10) == 0) {
        redirect_invalid_url(query);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not Found\r\n");
    }
}

int main() {
    const char *path = "/redirect/";
    const char *query = "https://example.com/somepage";

    handle_request(path, query);

    return 0;
}