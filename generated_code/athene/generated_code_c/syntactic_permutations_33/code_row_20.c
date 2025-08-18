#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 1 || url[url_len - domain_len - 1] != '.') return 0;

    for (size_t i = 0; i < domain_len; ++i) {
        if (url[url_len - domain_len + i] != domain[i]) return 0;
    }

    return 1;
}

const char* redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        return "Valid URL";
    } else {
        return "Error: Invalid URL domain";
    }
}

int main() {
    const char *test_urls[] = {
        "http://www.example.com",
        "https://subdomain.example.com/path?query=123",
        "http://invalid-domain.com",
        "https://example.net"
    };

    for (size_t i = 0; i < sizeof(test_urls) / sizeof(test_urls[0]); ++i) {
        printf("URL: %s -> %s\n", test_urls[i], redirect_invalid_url(test_urls[i]));
    }

    return 0;
}