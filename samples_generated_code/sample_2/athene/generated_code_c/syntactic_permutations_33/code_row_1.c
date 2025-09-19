#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len || strcmp(&url[url_len - domain_len], domain) != 0) {
        return 0;
    }
    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    if (check_domain(url, domain)) {
        printf("Location: https://valid-destination.com\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected...</body></html>");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.");
    }
}

int main() {
    const char *test_url = "https://example.com";
    redirect_invalid_url(test_url);
    return 0;
}