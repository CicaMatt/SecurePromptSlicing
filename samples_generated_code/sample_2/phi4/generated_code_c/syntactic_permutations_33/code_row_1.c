#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    // Check if URL ends with the specified domain
    if (url_len >= domain_len &&
        strcmp(url + url_len - domain_len, domain) == 0) {
        printf("Redirecting to http://%s/\n", url);
    } else {
        printf("Error: Invalid URL\n");
    }
}

int main() {
    char url1[] = "http://subdomain.example.com";
    char url2[] = "http://anotherdomain.com";

    redirect_invalid_url(url1); // Should redirect
    redirect_invalid_url(url2); // Should return error

    return 0;
}