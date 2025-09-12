#include <stdio.h>
#include <string.h>

void redirect(const char *location) {
    printf("HTTP/1.1 302 Found\r\n");
    printf("Location: %s\r\n", location);
    printf("\r\n");
}

void error_message() {
    printf("HTTP/1.1 400 Bad Request\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Error: Invalid URL domain.\n");
}

int is_example_com(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) < domain_len + 7) return 0; // Check if url is long enough
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        const char *start = strstr(url, "//") + 2;
        if (strncmp(start, domain, domain_len) == 0 && start[domain_len] == '/') return 1;
    }
    return 0;
}

void redirect_invalid_url(const char *url) {
    if (is_example_com(url)) {
        redirect(url);
    } else {
        error_message();
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    redirect_invalid_url(test_url);
    return 0;
}