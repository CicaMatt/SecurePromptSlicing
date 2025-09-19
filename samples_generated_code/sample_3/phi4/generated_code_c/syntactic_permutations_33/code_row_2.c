#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    const size_t domain_len = strlen(domain);

    // Find where the domain part starts (after the protocol and any slashes)
    const char *start = strstr(url, "//");
    if (!start) {
        printf("Error: Invalid URL format.\n");
        return;
    }
    start += 2; // Skip past "://"

    // Find end of the domain
    const char *end = strchr(start, '/');
    if (!end) {
        end = strpbrk(start, "\t\n\r\b\f\v"); // Handle URLs without path
    }

    size_t url_domain_len = end ? (size_t)(end - start) : strlen(start);

    // Check if the domain part matches "example.com"
    if (url_domain_len >= domain_len && 
        strncmp(start + url_domain_len - domain_len, domain, domain_len) == 0) {
        
        // Redirect to URL
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid domain. Only 'example.com' is allowed.\n");
    }
}

int main() {
    char test_url1[] = "http://www.example.com/page";
    char test_url2[] = "https://testsite.com/page";

    redirect_invalid_url(test_url1);
    redirect_invalid_url(test_url2);

    return 0;
}