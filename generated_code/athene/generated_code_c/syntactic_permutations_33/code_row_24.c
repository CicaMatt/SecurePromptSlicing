#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len + 1 || url[url_len - domain_len - 1] != '.') return 0;
    return !strcmp(&url[url_len - domain_len], domain);
}

void redirect_invalid_url(const char *input_url) {
    const char *domain = "example.com";
    if (check_domain(input_url, domain)) {
        printf("Location: %s\n", input_url);
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body>You are being redirected...</body></html>\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}