#include <stdio.h>
#include <string.h>

int redirect_url(const char *url) {
    const char *example_domain = "example.com";
    const char *delimiter = "//";

    // Find the start of the domain name by skipping protocol part
    const char *start_of_domain = strstr(url, delimiter);
    if (!start_of_domain) return 404; // No valid URL schema found

    start_of_domain += strlen(delimiter); // Move past the delimiter

    // Find the end of the domain name (either '/' or ':')
    const char *end_of_domain = strchr(start_of_domain, '/');
    if (!end_of_domain) {
        end_of_domain = strchr(start_of_domain, ':');
        if (!end_of_domain) return 404; // No valid ending found for domain
    }

    size_t domain_length = end_of_domain - start_of_domain;
    
    char domain[domain_length + 1];
    strncpy(domain, start_of_domain, domain_length);
    domain[domain_length] = '\0';

    if (strcmp(domain, example_domain) == 0) {
        return 200; // URL redirected
    } else {
        return 404; // Domain does not match example.com
    }
}

int main() {
    const char *url1 = "http://example.com/some/path";
    const char *url2 = "https://anotherdomain.com/page";

    int result1 = redirect_url(url1);
    int result2 = redirect_url(url2);

    printf("URL 1: %d\n", result1); // Expected: 200
    printf("URL 2: %d\n", result2); // Expected: 404

    return 0;
}