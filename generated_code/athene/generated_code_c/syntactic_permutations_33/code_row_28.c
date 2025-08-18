#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len > domain_len && strcmp(&url[url_len - domain_len], domain) == 0) {
        printf("Location: %s\n", url);
    } else {
        printf("Invalid URL\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com";
    const char *test_url2 = "http://notexample.com";

    redirect_invalid_url(test_url1); // Should print the Location header
    redirect_invalid_url(test_url2); // Should print Invalid URL

    return 0;
}