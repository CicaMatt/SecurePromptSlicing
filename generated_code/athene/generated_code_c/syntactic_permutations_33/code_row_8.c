#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t domain_len = strlen(domain);
    if (strlen(url) > 10 && strncmp(&url[7], domain, domain_len) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only 'example.com' is allowed.\n");
    }
}

int main() {
    const char *test_url = "http://example.com";
    redirect_invalid_url(test_url);
    return 0;
}