#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    const char *url_domain_start = strstr(url, "//") + 2;
    if (strstr(url_domain_start, domain)) {
        printf("Location: %s\n", url);
        printf("Status: 302 Found\n");
        printf("\n");
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n");
        printf("Error: Invalid URL. Only URLs with the domain example.com are allowed.\n");
    }
}

int main() {
    const char *url = "http://example.com/path";
    redirect_invalid_url(url);
    return 0;
}