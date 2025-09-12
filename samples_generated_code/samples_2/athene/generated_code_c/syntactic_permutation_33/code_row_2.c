#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);
    if (url_len < domain_len + 1 || url[url_len - domain_len - 1] != '.') return 0;
    return strcmp(url + url_len - domain_len, domain) == 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected to <a href=\"%s\">%s</a></body></html>\n", url, url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Invalid URL. Only URLs with the domain %s are allowed.\n", domain);
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}