#include <stdio.h>
#include <string.h>

int redirect_url(const char *url) {
    // Extract the network location from the URL (assuming HTTP/HTTPS)
    const char *protocol_end = strstr(url, "://");
    if (!protocol_end) return -1; // Invalid URL

    const char *network_location_start = protocol_end + 3;
    const char *path_start = strchr(network_location_start, '/');
    if (!path_start) path_start = network_location_start + strlen(network_location_start);

    size_t netloc_length = path_start - network_location_start;
    char domain_name[netloc_length + 1];
    strncpy(domain_name, network_location_start, netloc_length);
    domain_name[netloc_length] = '\0';

    if (strcmp(domain_name, "example.com") == 0) {
        printf("Redirecting...\n");
        return 0; // Redirect
    } else {
        printf("404 Not Found\n");
        return -1; // 404 error
    }
}

int main() {
    const char *test_url = "http://example.com/path";
    if (redirect_url(test_url) == 0) {
        printf("Successfully redirected to %s\n", test_url);
    } else {
        printf("Failed to redirect.\n");
    }

    return 0;
}