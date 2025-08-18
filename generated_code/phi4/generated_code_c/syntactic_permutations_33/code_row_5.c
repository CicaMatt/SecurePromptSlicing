#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    const size_t domain_len = strlen(domain);
    
    // Find where the domain part starts in the URL, assuming it's a valid URL format
    const char *start_of_domain = strstr(url, "//");
    if (!start_of_domain) return;  // Invalid URL format

    start_of_domain += 2;  // Skip "://"

    // Check if there is a subsequent '/' or end of string to identify the domain part
    const char *end_of_domain = strchr(start_of_domain, '/');
    if (!end_of_domain)
        end_of_domain = strlen(start_of_domain) + start_of_domain;

    size_t url_domain_len = end_of_domain - start_of_domain;
    
    if (url_domain_len == domain_len &&
        strncmp(start_of_domain, domain, domain_len) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only example.com is allowed.\n");
    }
}

int main() {
    char url1[] = "http://example.com/resource";
    char url2[] = "https://invalid.com/resource";

    redirect_invalid_url(url1);  // Should redirect
    redirect_invalid_url(url2);  // Should return error

    return 0;
}