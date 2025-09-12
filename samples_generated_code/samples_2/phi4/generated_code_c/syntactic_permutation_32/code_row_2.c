#include <stdio.h>
#include <string.h>

void handle_request(const char *path) {
    const char *redirect_prefix = "/redirect/";
    const int prefix_length = strlen(redirect_prefix);

    if (strncmp(path, redirect_prefix, prefix_length) == 0) {
        const char *url = path + prefix_length;
        
        // Check if the URL is from example.com
        if (strstr(url, "example.com") != NULL) {
            printf("Redirecting to: %s\n", url);
            // In a real application, you would redirect here.
        } else {
            printf("Error: The URL is not from example.com.\n");
        }
    } else {
        printf("Invalid route.\n");
    }
}

int main() {
    // Example usage
    handle_request("/redirect/http://example.com/page");
    handle_request("/redirect/http://not-example.com/page");
    handle_request("/other/route");

    return 0;
}