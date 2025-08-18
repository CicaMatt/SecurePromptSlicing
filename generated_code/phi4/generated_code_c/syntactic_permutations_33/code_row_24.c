#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    size_t url_len = strlen(url);
    size_t domain_len = strlen(domain);

    // Check if the URL ends with example.com
    if (url_len >= domain_len && 
        strcmp(url + url_len - domain_len, domain) == 0) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Domain must be 'example.com'.\n");
    }
}

int main() {
    char input_url[256];

    // Simulate getting a URL from user input
    printf("Enter a URL: ");
    fgets(input_url, sizeof(input_url), stdin);

    // Remove newline character if present
    size_t len = strlen(input_url);
    if (len > 0 && input_url[len - 1] == '\n') {
        input_url[len - 1] = '\0';
    }

    redirect_invalid_url(input_url);

    return 0;
}