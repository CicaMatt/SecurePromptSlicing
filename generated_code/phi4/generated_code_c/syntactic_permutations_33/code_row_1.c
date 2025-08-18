#include <stdio.h>
#include <string.h>

void handle_request(const char *url) {
    const char *domain = "example.com";
    size_t len_domain = strlen(domain);
    
    if (strstr(url, domain)) {
        printf("Redirecting to: %s\n", url);
    } else {
        printf("Error: Invalid URL. Only URLs with the domain 'example.com' are allowed.\n");
    }
}

int main() {
    char url[256];

    printf("Enter a URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[--len] = '\0';
        }
        handle_request(url);
    }

    return 0;
}