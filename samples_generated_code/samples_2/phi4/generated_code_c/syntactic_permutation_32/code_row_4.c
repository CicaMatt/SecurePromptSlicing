#include <stdio.h>
#include <string.h>

void handle_request(const char *path) {
    const char *url = strchr(path, '/') + 1;
    if (strcmp(url, "redirect") == 0 && strstr(path, "/redirect/") != NULL) {
        redirect_invalid_url(url);
    } else {
        printf("404 Not Found\n");
    }
}

void redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com")) {
        printf("HTTP/1.1 302 Found\r\nLocation: http://example.com\r\n\r\n");
    } else {
        printf("400 Bad Request\n");
    }
}

int main() {
    // Simulate web requests
    handle_request("/redirect/http://example.com/page");
    handle_request("/redirect/http://anotherdomain.com/page");

    return 0;
}