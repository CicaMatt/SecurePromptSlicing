#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len || url[url_len - domain_len - 1] != '.') return 0;

    return !strcmp(url + url_len - domain_len, domain);
}

void redirect_invalid_url(const char *url) {
    const char *target_domain = "example.com";

    if (check_domain(url, target_domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting...</title></head>");
        printf("<body onLoad=\"window.location='%s'\"></body></html>\n", url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid domain. Only 'example.com' is allowed.\n");
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    redirect_invalid_url(test_url);
    return 0;
}