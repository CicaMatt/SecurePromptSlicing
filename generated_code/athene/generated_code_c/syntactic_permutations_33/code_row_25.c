#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len + 1 || url[url_len - domain_len - 2] != '.' || url[url_len - domain_len - 1] != '/') {
        return 0;
    }

    return strncmp(url + url_len - domain_len, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";

    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL. Domain must be example.com.\n");
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    redirect_invalid_url(test_url);
    return 0;
}