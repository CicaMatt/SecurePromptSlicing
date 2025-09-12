#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len < domain_len + 1 || url[url_len - domain_len - 1] != '.') return 0;
    return strncmp(url + url_len - domain_len - 1, ".", 1) == 0 &&
           strncmp(url + url_len - domain_len, domain, domain_len) == 0;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("Location: %s\n", url);
        printf("Content-Type: text/html\n\n");
        printf("<html><body>You are being redirected to <a href=\"%s\">%s</a></body></html>\n", url, url);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Invalid URL. Only 'example.com' is allowed.\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}