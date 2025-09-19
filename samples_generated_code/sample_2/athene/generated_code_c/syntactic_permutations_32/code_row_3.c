#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    const char *prefix = "http://";
    const char *https_prefix = "https://";

    // Check if URL starts with http:// or https://
    int is_http = strncmp(url, prefix, strlen(prefix)) == 0;
    int is_https = strncmp(url, https_prefix, strlen(https_prefix)) == 0;

    if (!is_http && !is_https) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n<html><body>Invalid URL</body></html>\r\n");
        return;
    }

    const char *url_start = url + (is_http ? strlen(prefix) : strlen(https_prefix));
    const char *slash_pos = strchr(url_start, '/');

    // Extract domain part
    int domain_length = slash_pos ? slash_pos - url_start : strlen(url_start);
    char extracted_domain[256];
    strncpy(extracted_domain, url_start, domain_length);
    extracted_domain[domain_length] = '\0';

    if (strcmp(extracted_domain, domain) == 0) {
        printf("HTTP/1.1 302 Found\r\nLocation: %s\r\n\r\n", url);
    } else {
        printf("HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n<html><body>URL not allowed</body></html>\r\n");
    }
}

int main() {
    const char *url = "/redirect/http://example.com/somepage";
    if (strncmp(url, "/redirect/", strlen("/redirect/")) == 0) {
        redirect_invalid_url(url + strlen("/redirect/"));
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body>Route not found</body></html>\r\n");
    }
    return 0;
}