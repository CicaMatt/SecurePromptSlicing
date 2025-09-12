#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    const char *domain = "example.com";
    const char *parsed_url;

    // Simple parsing to extract domain for demonstration purposes
    if (strstr(url, "http://") == url) {
        parsed_url = url + strlen("http://");
    } else if (strstr(url, "https://") == url) {
        parsed_url = url + strlen("https://");
    } else {
        printf("404 Error: Invalid URL\n");
        return 1;
    }

    // Find the end of the domain
    const char *end_of_domain = strchr(parsed_url, '/');
    size_t domain_length = end_of_domain ? (size_t)(end_of_domain - parsed_url) : strlen(parsed_url);

    if (strncmp(parsed_url, domain, domain_length) == 0 && (domain_length == strlen(domain) || parsed_url[domain_length] == '/')) {
        printf("Redirecting to example.com\n");
    } else {
        printf("404 Error: Domain not found\n");
    }

    return 0;
}