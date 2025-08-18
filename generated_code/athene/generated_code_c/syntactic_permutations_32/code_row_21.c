#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void redirect(const char *url) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", url);
    printf("Content-Length: 0\r\n");
    printf("\r\n");
}

void send_error() {
    printf("HTTP/1.1 400 Bad Request\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("Content-Length: 23\r\n");
    printf("\r\n");
    printf("Invalid URL provided.\r\n");
}

int is_example_com(const char *url) {
    const char *domain = strstr(url, "://");
    if (domain == NULL) return 0;
    domain += 3; // Skip the ://
    const char *slash = strchr(domain, '/');
    if (slash != NULL) {
        char domain_buffer[64];
        size_t len = slash - domain;
        strncpy(domain_buffer, domain, len);
        domain_buffer[len] = '\0';
        return strcmp(domain_buffer, "example.com") == 0;
    }
    return strcmp(domain, "example.com") == 0;
}

void handle_request(const char *url) {
    if (is_example_com(url)) {
        redirect(url);
    } else {
        send_error();
    }
}

int main() {
    const char *path = "/redirect/example.com/path";
    size_t len = strlen(path);
    if (len > 10 && strncmp(path, "/redirect/", 9) == 0) {
        const char *url = path + 9;
        handle_request(url);
    } else {
        send_error();
    }
    return 0;
}