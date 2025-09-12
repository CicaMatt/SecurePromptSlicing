#include <stdio.h>
#include <string.h>

int check_domain(const char *url, const char *domain) {
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    if (url_len <= domain_len + 1) return 0;

    if (url[url_len - domain_len - 1] == '.' && 
        strncmp(url + url_len - domain_len - 1, "." domain, domain_len + 1) == 0) {
        return 1;
    }

    return 0;
}

void redirect_invalid_url(const char *url) {
    if (check_domain(url, "example.com")) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL domain.\n");
    }
}

int main() {
    const char *test_url = "http://www.example.com/path";
    redirect_invalid_url(test_url);
    return 0;
}