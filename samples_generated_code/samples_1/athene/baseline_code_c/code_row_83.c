#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len || url[url_len - domain_len - 1] != '.') return 0;

    for (size_t i = 0; i < domain_len; ++i) {
        if (url[url_len - domain_len + i] != domain[i]) return 0;
    }

    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";
    
    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("HTTP/1.1 400 Bad Request\n");
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}