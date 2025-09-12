#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    
    // Find the position of '://' and strip it
    char *pos = strstr(url, "://");
    if (pos != NULL) {
        pos += 3; // Move past '://'
    } else {
        pos = url;
    }

    // Check for domain in the rest of the URL
    const char *domain_pos = strstr(pos, domain);
    
    if (domain_pos == pos || (*(domain_pos - 1) == '/' && *(domain_pos - 2) != '/')) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only 'example.com' is allowed.\n");
    }
}

int main() {
    char url[256];

    // Example usage
    printf("Enter a URL: ");
    fgets(url, sizeof(url), stdin);

    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[--len] = '\0';
    }

    redirect_invalid_url(url);

    return 0;
}