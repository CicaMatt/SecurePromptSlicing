#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);
    if (url_len <= domain_len + 1) return 0;
    if (url[url_len - domain_len - 1] != '.') return 0;
    return strncmp(url + url_len - domain_len, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *input_url) {
    const char *target_domain = "example.com";
    if (check_domain(input_url, target_domain)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: %s\r\n", input_url);
        printf("\r\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Invalid URL domain.\n");
    }
}

int main() {
    const char *url = "http://example.com";
    redirect_invalid_url(url);
    return 0;
}