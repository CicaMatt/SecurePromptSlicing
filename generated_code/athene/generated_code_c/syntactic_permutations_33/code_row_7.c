#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    const char *prefix = "http://";
    const char *prefix_secure = "https://";
    size_t prefix_len = strlen(prefix);
    size_t prefix_secure_len = strlen(prefix_secure);

    if (strncmp(url, prefix, prefix_len) == 0) {
        url += prefix_len;
    } else if (strncmp(url, prefix_secure, prefix_secure_len) == 0) {
        url += prefix_secure_len;
    }

    const char *slash_pos = strchr(url, '/');
    const char *domain_start = url;
    size_t domain_length;

    if (slash_pos != NULL) {
        domain_length = slash_pos - domain_start;
    } else {
        domain_length = strlen(domain_start);
    }

    return strncmp(domain_start, domain, domain_length) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *valid_domain = "example.com";

    if (check_domain(url, valid_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com/path";
    const char *test_url2 = "https://invalid.com/path";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}