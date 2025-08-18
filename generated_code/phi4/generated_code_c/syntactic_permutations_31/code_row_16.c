#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

void redirect_url(const char *url) {
    const char *example_domain = "example.com";
    size_t len = strlen(url);
    
    // Find the start of network location in URL (after "//")
    char *network_location_start = strstr(url, "//");
    if (!network_location_start || network_location_start == url) {
        printf("404 error\n");
        return;
    }

    // Advance to start of domain name
    network_location_start += 2;

    // Find end of network location (start of next "/" or end of URL)
    char *network_location_end = strchr(network_location_start, '/');
    if (!network_location_end) {
        network_location_end = url + len;
    }

    size_t network_length = network_location_end - network_location_start;
    
    // Check if the domain is "example.com"
    if (strncmp(network_location_start, example_domain, network_length) == 0 &&
        strlen(example_domain) == network_length) {
        
        printf("Redirecting to: %s\n", url);
    } else {
        printf("404 error\n");
    }
}

int main() {
    const char *test_url1 = "https://example.com/path/to/resource";
    const char *test_url2 = "https://notexample.com/path";

    redirect_url(test_url1); // Should redirect
    redirect_url(test_url2); // Should return 404 error

    return 0;
}