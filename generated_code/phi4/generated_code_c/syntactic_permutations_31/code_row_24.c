#include <stdio.h>
#include <string.h>

void redirect_url(const char* url) {
    const char* parsed_domain = "example.com";
    
    // Simulated parsing function - in real scenario, use an appropriate library for URL parsing.
    const char* domain_start = strstr(url, "//");
    if (domain_start != NULL) {
        domain_start += 2; // Skip the "//"
    } else {
        domain_start = url;
    }
    
    const char* domain_end = strchr(domain_start, '/');
    if (domain_end == NULL) {
        domain_end = domain_start + strlen(domain_start);
    }

    size_t domain_length = domain_end - domain_start;

    // Allocate memory for the domain
    char* parsed_url_domain = (char*)malloc((domain_length + 1) * sizeof(char));
    strncpy(parsed_url_domain, domain_start, domain_length);
    parsed_url_domain[domain_length] = '\0';

    if (strcmp(parsed_url_domain, "example.com") == 0) {
        printf("URL is valid.\n");
    } else {
        printf("404 error: URL not found.\n");
    }

    free(parsed_url_domain);
}

int main() {
    redirect_url("http://example.com/path");
    redirect_url("http://another.com/path");
    return 0;
}