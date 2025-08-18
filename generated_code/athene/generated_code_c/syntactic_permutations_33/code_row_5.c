#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len + 1) return 0;
    if (url[url_len - domain_len - 1] != '.') return 0;

    for (size_t i = 0; i < domain_len; ++i) {
        if (url[url_len - domain_len + i] != domain[i]) return 0;
    }

    return 1;
}

void redirect_invalid_url(const char *url) {
    const char *example_domain = "example.com";
    
    if (check_domain(url, example_domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com/path";
    const char *test_url2 = "http://wrongdomain.com/path";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}