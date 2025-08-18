#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len || strcmp(&url[url_len - domain_len], domain) != 0) {
        return 0;
    }

    for (int i = url_len - domain_len - 1; i >= 0; --i) {
        if (url[i] == '/') {
            return url[i + 1] == 'w' && url[i + 2] == '.' || url[i + 1] == 'h' && url[i + 2] == 't' && url[i + 3] == 't' && url[i + 4] == 'p';
        }
    }

    return 0;
}

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (check_domain(url, domain)) {
        printf("Location: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs with the domain example.com are allowed.\n");
    }
}

int main() {
    const char *test_url1 = "http://example.com";
    const char *test_url2 = "https://wrongdomain.com";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}